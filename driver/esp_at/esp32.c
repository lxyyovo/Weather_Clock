#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "usart.h"
#include "delay.h"
#include "esp32.h"
#include "weather.h"
#include "page.h"

#define ESP_AT_DEBUG    1   // 调试模式，打印 AT 命令和应答(0: 关闭, 1: 开启)

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

extern UART_HandleTypeDef huart1;

typedef enum
{
    AT_ACK_NONE,
    AT_ACK_OK,
    AT_ACK_ERROR,
    AT_ACK_BUSY,
    AT_ACK_READY,
} at_ack_t;

typedef struct
{
    at_ack_t ack;
    const char *string;
} at_ack_match_t;

static const at_ack_match_t at_ack_matches[] = 
{
    {AT_ACK_OK, "OK\r\n"},
    {AT_ACK_ERROR, "ERROR\r\n"},
    {AT_ACK_BUSY, "busy p...\r\n"},
    {AT_ACK_READY, "ready\r\n"},
};

static char rxbuf[1024];
static bool esp_at_wait_boot(uint32_t timeout);

// printf 重定向到串口2（调试口），串口1 专用于 ESP32 AT 通信
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 100);
    return ch;
}

// 发送 AT 命令（自动补 CRLF）
static void esp_at_usart_write(const char *data)
{
    if (data == NULL)
        return;

    HAL_UART_Transmit(&huart1, (uint8_t *)data, (uint16_t)strlen(data), HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1, (uint8_t *)"\r\n", 2, HAL_MAX_DELAY);
}

// ESP32 初始化（AT 测试 → RESTORE → 等待 ready）
bool esp_at_init(void)
{
    if (!esp_at_wait_boot(3000))//等待AT初始化完成
        return false;
    if (!esp_at_write_command("AT+RESTORE", 2000))
        return false;
    if (!esp_at_wait_ready(5000))
        return false;

    return true;
}

// 匹配应答字符串并返回对应 ACK 类型
static at_ack_t match_internal_ack(const char *str)
{
    for (uint32_t i = 0; i < ARRAY_SIZE(at_ack_matches); i++)
    {
        if (strcmp(str, at_ack_matches[i].string) == 0)
            return at_ack_matches[i].ack;
    }

    return AT_ACK_NONE;
}

// 等待接收应答，按行匹配并带超时
static at_ack_t esp_at_usart_wait_receive(uint32_t timeout)
{
    uint32_t rxlen = 0;
    const char *line = rxbuf;
    uint64_t start = HAL_GetTick();

    rxbuf[0] = '\0';
    while (rxlen < sizeof(rxbuf) - 1)
    {
        uint32_t elapsed = (uint32_t)(HAL_GetTick() - start);
        if (elapsed >= timeout)
            return AT_ACK_NONE;

        uint8_t ch;
        if (HAL_UART_Receive(&huart1, &ch, 1, timeout - elapsed) != HAL_OK)
            return AT_ACK_NONE;

        rxbuf[rxlen++] = (char)ch;
        rxbuf[rxlen] = '\0';
        if (rxbuf[rxlen - 1] == '\n')
        {
            at_ack_t ack = match_internal_ack(line);
            if (ack != AT_ACK_NONE)
                return ack;
            line = rxbuf + rxlen;
        }
    }

    return AT_ACK_NONE;
}

// 等待模块返回 ready
bool esp_at_wait_ready(uint32_t timeout)
{
    return esp_at_usart_wait_receive(timeout) == AT_ACK_READY;
}

// 发送 AT 命令并等待 OK 应答
bool esp_at_write_command(const char *command, uint32_t timeout)
{
#if ESP_AT_DEBUG
    printf("[DEBUG] Send: %s\n", command);
#endif

    esp_at_usart_write(command);
    at_ack_t ack = esp_at_usart_wait_receive(timeout);

#if ESP_AT_DEBUG
    printf("[DEBUG] Response:\n%s\n", rxbuf);
#endif

    return ack == AT_ACK_OK;
}

// 获取最近一次应答缓冲区
const char *esp_at_get_response(void)
{
    return rxbuf;
}

// 等待模块引导完成（发送 AT 命令并等待 OK 应答）
static bool esp_at_wait_boot(uint32_t timeout)
{
    for(int t = 0; t < timeout; t += 100)
    {
        if (esp_at_write_command("AT", 100))
            return true;
    }
    return false;
}

// 设置 WiFi 模式为 station
bool esp_at_wifi_init(void)
{
    return esp_at_write_command("AT+CWMODE=1", 2000);
}

// 连接 WiFi（可附带 MAC）
bool esp_at_connect_wifi(const char *ssid, const char *pwd, const char *mac)
{
    if (ssid == NULL || pwd == NULL)
        return false;

    char cmd[128];
    int len = snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"", ssid, pwd);
    if (mac)
        snprintf(cmd + len, sizeof(cmd) - len, ",\"%s\"", mac);

    return esp_at_write_command(cmd, 5000);
}

// 解析 +CWSTATE 应答，提取连接状态和 SSID
static bool parse_cwstate_response(const char *response, esp_wifi_info_t *info)
{
    // AT+CWSTATE?
    // +CWSTATE:2,"HONOR 200 Prom"

    // OK
    response = strstr(response, "+CWSTATE:");
    if (response == NULL)
        return false;

    int wifi_state;
    if (sscanf(response, "+CWSTATE:%d,\"%63[^\"]", &wifi_state, info->ssid) != 2)
        return false;

    info->connected = (wifi_state == 2);

    return true;
}

// 解析 +CWJAP 应答，提取 AP 信息
static bool parse_cwjap_response(const char *response, esp_wifi_info_t *info)
{
    // AT+CWJAP?
    // +CWJAP:"HONOR 200 Prom","aa:a2:6c:2b:f8:ee",11,-23,0,1,3,0,1

    // OK
    response = strstr(response, "+CWJAP:");
    if (response == NULL)
        return false;

    if (sscanf(response, "+CWJAP:\"%63[^\"]\",\"%17[^\"]\",%d,%d", info->ssid, info->bssid, &info->channel, &info->rssi) != 4)
        return false;

    return true;
}

// 查询并解析 WiFi 连接信息
bool esp_at_get_wifi_info(esp_wifi_info_t *info)
{
    if (!esp_at_write_command("AT+CWSTATE?", 2000))
        return false;

    if (!parse_cwstate_response(esp_at_get_response(), info))
        return false;

    if(info->connected == true)
    {
        if (!esp_at_write_command("AT+CWJAP?", 2000))
        return false;

        if (!parse_cwjap_response(esp_at_get_response(), info))
        return false;
    }
    
    return true;
}

// 查询 WiFi 是否已连接
bool wifi_is_connected(void)
{
    esp_wifi_info_t info;
    if (esp_at_get_wifi_info(&info))
    {
        return info.connected;
    }
    return false;
}

// 配置 SNTP（时区 8，东八区）
bool esp_at_sntp_init(void)
{
    if (!esp_at_write_command("AT+CIPSNTPCFG=1,8", 2000))
        return false;

    return true;
}

// 英文月份缩写转数字
static uint8_t month_str_to_num(const char *month_str)
{
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for (uint8_t i = 0; i < 12; i++)
    {
        if (strcmp(month_str, months[i]) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}

// 英文星期缩写转数字
static uint8_t weekday_str_to_num(const char *weekday_str)
{
    const char *weekdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    for (uint8_t i = 0; i < 7; i++) {
        if (strcmp(weekday_str, weekdays[i]) == 0)
        {
            return i + 1;
        }
    }
    return 0;
}

// 解析 +CIPSNTPTIME 应答，提取日期时间
static bool parse_cipsntptime_response(const char *response, esp_date_time_t *date)
{
    char weekday_str[8];
    char month_str[4];
    response = strstr(response, "+CIPSNTPTIME:");
    if (sscanf(response, "+CIPSNTPTIME:%3s %3s %hhu %hhu:%hhu:%hhu %hu", 
               weekday_str, month_str, 
               &date->day, &date->hour, &date->minute, &date->second, &date->year) != 7)
        return false;

    date->weekday = weekday_str_to_num(weekday_str);
    date->month = month_str_to_num(month_str);

    return true;
}

// 获取网络时间
bool esp_at_sntp_get_time(esp_date_time_t *date)
{
    if (!esp_at_write_command("AT+CIPSNTPTIME?", 2000))
        return false;

    if (!parse_cipsntptime_response(esp_at_get_response(), date))
        return false;

    return true;
}

// 发送 HTTP GET 请求并返回应答
const char *esp_at_http_get(const char *url)
{
    // AT+HTTPCLIENT=2,1,"https://api.seniverse.com/v3/weather/now.json?key=SqBhSRMmPB7-70QzD&location=Shaoguan&language=en&unit=c",,,2
    // +HTTPCLIENT:274,{"results":[{"location":{"id":"WS2V1N2FZZ77","name":"Shaoguan","country":"CN","path":"Shaoguan,Shaoguan,Guangdong,China","timezone":"Asia/Shanghai","timezone_offset":"+08:00"},"now":{"text":"Foggy","code":"30","temperature":"27"},"last_update":"2026-09-20T23:04:11+08:00"}]}

    // OK
    char *txbuf = rxbuf;
    snprintf(txbuf, sizeof(rxbuf), "AT+HTTPCLIENT=2,1,\"%s\",,,2", url);
    bool ret = esp_at_write_command(txbuf, 5000);
    return ret ? esp_at_get_response() : NULL;
}
