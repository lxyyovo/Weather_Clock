# Weather Clock | 天气时钟

基于 **STM32F407 + ESP32(AT 固件)** 的联网桌面天气时钟：2.4 寸 ST7789 屏显示时间日期、室内温湿度与室外天气，时间通过 SNTP 自动校时。

## 功能特性

- **时间显示**：RTC 走时（LSE 32.768kHz 晶振，掉电由 VBAT 维持），大字号时:分，秒通过冒号闪烁体现
- **自动校时**：上电与每天通过 ESP32 SNTP（东八区）同步一次网络时间，失败 5 秒后重试
- **室内环境**：AHT20 采集温度与湿度，每 3 秒刷新一次
- **室外天气**：心知天气 API 获取实时温度与天气现象，每分钟刷新，按天气码映射 8 种图标
- **WiFi 状态**：显示当前连接 SSID，断连时提示
- **开机引导页 / 错误提示页**：启动动画与初始化失败提示
- **非阻塞主循环**：SysTick 每毫秒回调驱动软件定时器，周期任务轮询调度，无阻塞等待任务

## 界面布局

屏幕 240×320，竖屏（`ST7789_ROTATION 2`），分为三块区域：

<img width="416" height="474" alt="image" src="https://github.com/user-attachments/assets/a2d7f1bc-0ea7-4e1e-8199-c370e2be1165" />

- 上方时间区：WiFi 图标与 SSID，76 号字时间（秒通过冒号闪烁表示），20 号字日期与星期
- 左下室内区：AHT20 温度（54 号字）与湿度（64 号字）
- 右下室外区：城市名、室外温度（54 号字）与天气图标

## 硬件

| 模块 | 型号 / 说明 |
| --- | --- |
| 主控 | STM32F407VET6（LQFP100，512KB Flash / 192KB SRAM） |
| 显示屏 | ST7789 2.4 寸 240×320，SPI，RGB565 |
| 无线模块 | ESP32 串口 AT 固件（负责 WiFi / SNTP / HTTP） |
| 温湿度 | AHT20，I2C，地址 0x38 |
| 外部晶振 | HSE 8MHz（主时钟）、LSE 32.768kHz（RTC） |

### 引脚连接

| 功能 | STM32 引脚 | 说明 |
| --- | --- | --- |
| LCD SCK | PB13 | SPI2_SCK |
| LCD MOSI | PB15 | SPI2_MOSI |
| LCD CS | PB12 | 软件片选 |
| LCD DC | PB1 | 命令/数据 |
| LCD RST | PB0 | 复位 |
| ESP32 TX/RX | PA9 / PA10 | USART1，115200，AT 指令 |
| 调试串口 | PA2 / PA3 | USART2，115200，`printf` 输出 |
| AHT20 SCL/SDA | PB6 / PB7 | I2C1，上拉 |
| 按键（预留） | PE3 / PE4 | 内部上拉输入 |

时钟树：HSE 8MHz → PLL(M=8, N=336, P=2) → **SYSCLK 168MHz**，APB1 42MHz / APB2 84MHz。

## 目录结构

```
Weather_Clock/
├── app/                     # 应用层
│   ├── page/                #   页面与局部重绘（page.c）
│   ├── font/                #   中英文字库 + 整屏点阵图（fonts*.c）
│   ├── image/               #   天气图标点阵（image.c）
│   ├── weather.c            #   心知天气 JSON 解析
│   └── wifi.c               #   WiFi 初始化与连接流程
├── driver/                  # 驱动层
│   ├── st7789/              #   LCD 驱动（绘图 / 文字 / 图片）
│   ├── esp_at/              #   ESP32 AT 指令封装
│   ├── aht20/               #   AHT20 温湿度驱动
│   ├── rtc/                 #   RTC 读写封装
│   ├── delay/               #   SysTick 微秒延时 + 周期回调
│   ├── key/                 #   按键状态机（预留，暂未调用）
│   └── mloop/               #   主循环与周期任务调度
├── Core/                    # CubeMX 生成的 HAL 初始化（Inc / Src）
├── Drivers/                 # CMSIS + STM32F4 HAL 库
├── MDK-ARM/                 # Keil MDK 工程（Weather_Clock.uvprojx）
├── resources/               # 界面素材原图（不参与编译）
│   ├── design/              #   页面效果图（欢迎 / WiFi / 主页 / 错误页）
│   └── images/              #   图标与点阵原图（jpg 预览、png 取模）
├── City Weather/            # 心知天气城市列表（城市 ID 对照表）
├── Image2Lcd 2.9(破解版)/    # 图片取模工具（图片 → 点阵数组）
├── PCtoLCD2002/             # 字体取模工具（字符 → 点阵字库）
├── MapleMono-NF-CN-unhinted/# 取模所用字体 Maple Mono（16 个字重）
└── Weather_Clock.ioc        # CubeMX 配置文件
```

`resources/`、`City Weather/` 以及两个取模工具和字体目录都只是本地素材与工具，不参与编译；素材如何转成固件里的点阵数组见下文「素材与取模」。

## 运行流程

```
上电 → HAL/CubeMX 外设初始化 → SysTick 周期回调 → LCD 初始化 → AHT20 初始化
     → 开机页 welcome_page
     → WiFi 初始化（ESP32 AT → CWMODE=1 → SNTP 配置）
     → WiFi 连接等待（WiFi 页，超时 10s 失败则显示错误页）
     → 主页面 main_page
     → 死循环 main_loop() 轮询
```

周期任务（见 `driver/mloop/mloop.c`）：

| 任务 | 周期 | 说明 |
| --- | --- | --- |
| `time_sync` | 1 天 | SNTP 校时，失败降为 5 秒重试 |
| `wifi_update` | 5 秒 | 查询 WiFi 状态，变化才重绘 |
| `time_update` | 1 秒 | 刷新时间/日期，值变化才重绘 |
| `inner_update` | 3 秒 | 读 AHT20，刷新室内温湿度 |
| `outdoor_update` | 1 分钟 | HTTP 请求天气，刷新温度与图标 |

## 素材与取模

界面里的图标和字库都是先在 PC 上取模成 C 数组，再编进固件：

| 素材 | 工具 | 输出 |
| --- | --- | --- |
| `resources/images/` 图标原图（jpg 预览、png 取模） | `Image2Lcd 2.9(破解版)/Img2Lcd.exe` | RGB565 数组，放入 `app/image/image.c` |
| `MapleMono-NF-CN-unhinted/` 字体 | `PCtoLCD2002/PCtoLCD2002.exe` | 点阵字库，放入 `app/font/fonts*.c` |

字体取模前需要先把字体装进系统，PCtoLCD2002 的字体下拉框才能选到：在 `MapleMono-NF-CN-unhinted/` 里全选 `.ttf` 文件，右键 → **为所有用户安装**。

该字体为 Maple Mono v7.9，采用 SIL OFL 1.1 许可（见目录内 `LICENSE.txt`），与本项目的 GPL-3.0 相互独立。

## 编译与烧录

1. 用 **Keil MDK 5** 打开 `MDK-ARM/Weather_Clock.uvprojx`
2. 确认 `Options for Target → Target` 中 **勾选 `Use MicroLIB`**（启动文件按 MicroLIB 条件编译，与库设置不一致会报 `__initial_sp` / `__use_two_region_memory` 未定义）
3. **每次修改库设置或外设配置后，先 `Project → Clean Targets` 再 `Rebuild all target files`**
4. `Options for Target → Debug` 选择 ST-Link Debugger，Flash 算法 `STM32F4xx_512.FLM`，起始地址 `0x08000000`
5. 下载后按复位即可运行；调试口接 USART2（115200）可查看运行日志

## 配置说明

| 配置项 | 位置 |
| --- | --- |
| WiFi 名称 / 密码 | `app/page/page.h` 的 `WIFI_SSID` / `WIFI_PASSWD` |
| 天气 API 地址（密钥、城市） | `driver/mloop/mloop.c` 的 `outdoor_update()` |
| 各任务刷新周期 | `driver/mloop/mloop.c` 顶部宏定义 |
| AT 指令调试打印开关 | `driver/esp_at/esp32.c` 的 `ESP_AT_DEBUG` |
| 屏幕分辨率 / 旋转方向 | `driver/st7789/st7789.h` 的 `USING_240X320` / `ST7789_ROTATION` |

> 天气数据来自[心知天气](https://www.seniverse.com/)免费版 API。免费版**只支持国内 370 个主要城市**，可用数据也仅限天气实况（天气现象 + 气温）、未来 3 天预报与 6 项生活指数，超出范围的城市需要付费版。
>
> 城市当前固定为韶关，可在 `outdoor_update()` 的 URL 里修改 `location` 参数，取值支持城市 ID、汉字名、拼音三种写法。城市 ID 与名称的对照表见 `City Weather/城市列表20230505.xls`，共 3 个工作表：`国内城市`（3218 条，字段为城市 ID / 行政归属 / 城市简称 / 拼音）、`国际城市`（21798 条）、`国家和地区`（251 条）。注意该表是全量列表，免费版实际可用的只有其中 370 个主要城市。

## 常见问题

- **屏幕白屏，但接调试器运行正常**：绝大多数是构建产物不同步。库设置（MicroLIB）或外设配置改动后 `startup_stm32f407xx.o` 未重新汇编，链接出的固件异常。执行 **Clean + Rebuild** 即可。
- **链接报 `__initial_sp` / `__use_two_region_memory` 未定义**：同上一原因，启动文件与 C 库的 MicroLIB 开关不匹配，同样通过 Clean + Rebuild 解决。
- **卡死在 `Error_Handler()`**：时钟配置失败。确认板上 HSE 为 8MHz，且 RTC 用的 32.768kHz 晶振已焊接并能起振，否则 `RCC_LSE_ON` 会超时进错误处理。
- **室外温度一直显示 `--`**：串口日志可区分原因——`http error` 是 ESP32 联网/请求失败，`parse failed` 是接口返回格式与解析不匹配。
- **换了城市后天气查不到**：心知天气免费版只覆盖国内 370 个主要城市，换成区县或非主要城市会返回 `no result`。对照 `City Weather/城市列表20230505.xls` 换成范围内城市的 ID 或拼音。
- **室内温度显示乱码/异常**：`main_page_redraw_inner_humidity()` 的缓冲区未初始化，值超出范围时会绘制栈上的随机内容（详见下方待办）。

## 待办与已知问题

- [ ] `main_page_redraw_inner_humidity()` 的 `char str[3]` 缺少初始化，无效值时显示随机内容
- [ ] 温度/湿度格式化缓冲区为 3 字节，边界值（如 `100` / `-10`）会被 `snprintf` 截断，建议收紧取值条件
- [ ] 城市名与错误信息过长时，`snprintf` 按字节截断可能切断 UTF-8 汉字；错误页居中计算存在无符号下溢风险
- [ ] `driver/key/` 按键模块已实现但未接入主循环
- [ ] WiFi 密码与 API 密钥明文写在源码中，建议抽到独立的 `config.h`（并加入 `.gitignore`）

## 许可与致谢

本项目是开源天气时钟项目的个人移植实现：界面布局、字库与图片素材沿用原项目，驱动与应用层改用 STM32 HAL 库重写。

原项目采用 **GPL-3.0** 许可证，依据其传染性要求，本项目作为衍生作品同样以 **GPL-3.0** 发布（完整协议文本见 `LICENSE`）。原始版权声明予以保留，主要修改见 git 提交记录。
