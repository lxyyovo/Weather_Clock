#include <stdio.h>
#include <string.h>
#include "st7789.h"
#include "fonts.h"
#include "page.h"
#include "rtctime.h"

static const uint16_t color_bg_time = 0xFFDF;//#F8F8F8
static const uint16_t color_bg_inner = 0x8EDD;//#88D9EA
static const uint16_t color_bg_outdoor = 0xFC29;//#FE874B

// 计算字符串按指定字体渲染后的总像素宽度（UTF-8 汉字占3字节）
static uint16_t str_width(const char *s, const font_def_t *f)
{
    uint16_t w = 0;
    const uint8_t *p = (const uint8_t *)s;
    while (*p) {
        if (*p < 0x80) { p++; w += f->ascii_w; }
        else { p += 3; w += f->cn_w; }
    }
    return w;
}

// 重绘WiFi SSID
void main_page_redraw_wifi_ssid(const char *ssid)
{
    char str[21];
    snprintf(str, sizeof(str), "%20s", ssid);
    ST7789_DrawString(50, 23, str, &font_16, 0x8C71, color_bg_time);
}

// 重绘时间
void main_page_redraw_time(rtc_date_time_t *time)
{
    char str[6];
    snprintf(str, sizeof(str), "%02u%c%02u", time->hour, (time->second % 2 == 0) ? ':' : ' ', time->minute);
    ST7789_DrawString(29, 42, str, &font_76, BLACK, color_bg_time);
}

// 重绘日期
void main_page_redraw_date(rtc_date_time_t *date)
{
    char str[24];
    snprintf(str, sizeof(str), "%04u/%02u/%02u 星期%s", date->year, date->month, date->day,
        date->weekday == 1 ? "一":
        date->weekday == 2 ? "二":
        date->weekday == 3 ? "三":
        date->weekday == 4 ? "四":
        date->weekday == 5 ? "五":
        date->weekday == 6 ? "六":
        date->weekday == 7 ? "天":
        "X"
    );
    ST7789_DrawString(35, 121, str, &font_20, 0x8C71, color_bg_time);
}

// 重绘室内温度
void main_page_redraw_inner_temperature(float temperature)
{
    char str[3] = {'-', '-'};
    if (temperature > -10.0f && temperature <= 100.0f)
        snprintf(str, sizeof(str), "%2.0f", temperature);
    ST7789_DrawString(30, 192, str, &font_54_bold, BLACK, color_bg_inner);
}

// 重绘室内湿度
void main_page_redraw_inner_humidity(float humidity)
{
    char str[3];
    if (humidity > 0.0f && humidity <= 99.99f)
        snprintf(str, sizeof(str), "%2.0f", humidity);
    ST7789_DrawString(25, 239, str, &font_64, BLACK, color_bg_inner);
}

// 重绘城市
void main_page_redraw_outdoor_city(const char *city)
{
    char str[9];
    snprintf(str, sizeof(str), "%s", city);
    ST7789_DrawString(127, 170, str, &font_24_semibold, BLACK, color_bg_outdoor);
}

// 重绘室外温度
void main_page_redraw_outdoor_temperature(float temperature)
{
    char str[3] = {'-', '-'};
    if (temperature > -10.0f && temperature <= 100.0f)
        snprintf(str, sizeof(str), "%2.0f", temperature);
    ST7789_DrawString(135, 190, str, &font_54_bold, BLACK, color_bg_outdoor);
}

// 重绘天气图标
void main_page_redraw_outdoor_weather_icon(const int code)
{
    const unsigned char *icon;
    if (code == 0 || code == 2 || code == 38)
        icon = gImage_icon_qing;
    else if (code == 1 || code == 3)
        icon = gImage_icon_yueliang;
    else if (code == 4 || code == 9)
        icon = gImage_icon_yintian;
    else if (code == 5 || code == 6 || code == 7 || code == 8)
        icon = gImage_icon_duoyun;
    else if (code == 10 || code == 13 || code == 14 || code == 15 || code == 16 || code == 17 || code == 18 || code == 19)
        icon = gImage_icon_zhongyu;
    else if (code == 11 || code == 12)
        icon = gImage_icon_leizhenyu;
    else if (code == 20 || code == 21 || code == 22 || code == 23 || code == 24 || code == 25)
        icon = gImage_icon_zhongxue;
    else // 扬沙、龙卷风等
        icon = gImage_icon_na;

    ST7789_DrawImage(166, 240, 54, 54, (uint16_t *)icon);
}


void welcome_page(void)
{
    ST7789_Fill_Color(BLACK);//背景颜色
    ST7789_DrawImage(30, 10, 180, 180, (uint16_t *)gImage_hua);
    ST7789_DrawString(40, 205, "梅花嵌入式", &font_32, 0xEC12, BLACK);
    ST7789_DrawString(56, 237, "天气时钟", &font_32, 0x553F, BLACK);
    ST7789_DrawString(40, 280, "loading...", &font_24_bold, WHITE, BLACK);
}

void error_page(const char *msg)
{
    uint16_t startx = (ST7789_WIDTH - str_width(msg, &font_20)) / 2;//居中显示

    ST7789_Fill_Color(BLACK);//背景颜色
    ST7789_DrawImage(40, 37, 160, 160, (uint16_t *)gImage_error);
    ST7789_DrawString(startx, 245, msg, &font_20, YELLOW, BLACK);
}

void wifi_page(void)
{
    static const char *ssid = WIFI_SSID;
    uint16_t startx = (ST7789_WIDTH - str_width(ssid, &font_20)) / 2;//居中显示

    ST7789_Fill_Color(BLACK);//背景颜色
    ST7789_DrawImage(30, 15, 180, 164, (uint16_t *)gImage_wifi);
    ST7789_DrawString(88, 191, "WIFI", &font_32, 0x07FD, BLACK);
    ST7789_DrawString(startx, 231, ssid, &font_20, WHITE, BLACK);
    ST7789_DrawString(84, 263, "连接中", &font_24_bold, 0x963F, BLACK);
}

void main_page(void)
{
    ST7789_Fill_Color(BLACK);//背景颜色

    //上矩形部分
    do {
        ST7789_Fill(15, 15, 224, 154, color_bg_time);
        ST7789_DrawImage(23, 20, 24, 24, (uint16_t *)gImage_icon_wifi);//WiFi 图标
        main_page_redraw_wifi_ssid(WIFI_SSID);//SSID 文字
        ST7789_DrawString(29, 42, "--:--", &font_76, BLACK, color_bg_time);//时间 
        ST7789_DrawString(35, 121, "----/--/-- 星期X", &font_20, 0x8C71, color_bg_time);//日期 "2026/09/28 星期一"
    } while (0);    // 循环一次

    //左下矩形部分
    do {
        ST7789_Fill(15, 165, 114, 304, color_bg_inner);
        ST7789_DrawString(18, 170, "室内环境", &font_24_semibold, BLACK, color_bg_inner);
        ST7789_DrawString(86, 191, "C", &font_32, BLACK, color_bg_inner);
        ST7789_DrawString(91, 262, "%", &font_32, BLACK, color_bg_inner);
        main_page_redraw_inner_temperature(999.9f);//室内温度 --
        main_page_redraw_inner_humidity(999.9f);//室内湿度 --
    } while (0);    // 循环一次


    //右下矩形部分
    do {
        ST7789_Fill(125, 165, 224, 304, color_bg_outdoor);
        ST7789_DrawString(192, 189, "C", &font_32, BLACK, color_bg_outdoor);
        ST7789_DrawImage(136, 243, 21, 51, (uint16_t *)gImage_icon_wenduji);
        main_page_redraw_outdoor_city("韶关");//城市 
        main_page_redraw_outdoor_temperature(999.9f);//室外温度
        main_page_redraw_outdoor_weather_icon(-1);//天气图标
    } while (0);    // 循环一次
}

void main2_page(void)
{
    ST7789_Fill_Color(BLACK);//背景颜色

    //上矩形部分
    do {
        ST7789_Fill(15, 15, 224, 154, color_bg_time);
       
    } while (0);    // 循环一次

    //左下矩形部分
    do {
        ST7789_Fill(15, 165, 114, 304, color_bg_inner);
    
    } while (0);    // 循环一次


    //右下矩形部分
    do {
        ST7789_Fill(125, 165, 224, 304, color_bg_outdoor);
   
    } while (0);    // 循环一次
}
