#ifndef _page_h
#define _page_h

#include "rtctime.h"

#define APP_VERSION     "v1.0"
#define WIFI_SSID       "HONOR 200 Prom"
#define WIFI_PASSWD     "99999999"
//#define WEATHER_URL     "https://api.seniverse.com/v3/weather/now.json?key=SqBhSRMmPB7-70QzD&location=Shaoguan&language=en&unit=c";

void welcome_page(void);
void error_page(const char *msg);
void wifi_page(void);
void main_page(void);

// 主页面局部重绘
void main_page_redraw_time(rtc_date_time_t *time);
void main_page_redraw_date(rtc_date_time_t *date);
void main_page_redraw_wifi_ssid(const char *ssid);
void main_page_redraw_inner_temperature(float temperature);
void main_page_redraw_inner_humidity(float humidity);
void main_page_redraw_outdoor_city(const char *city);
void main_page_redraw_outdoor_temperature(float temperature);
void main_page_redraw_outdoor_weather_icon(const int code);

#endif
