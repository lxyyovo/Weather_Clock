#include <string.h>
#include "rtctime.h"
#include "rtc.h"

static void _rtc_set_time_once(const rtc_date_time_t *date_time)
{
    RTC_DateTypeDef date = {0};
    RTC_TimeTypeDef time = {0};

    date.Year = date_time->year - 2000;
    date.Month = date_time->month;
    date.Date = date_time->day;
    date.WeekDay = date_time->weekday;

    time.Hours = date_time->hour;
    time.Minutes = date_time->minute;
    time.Seconds = date_time->second;

    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);
}

static void _rtc_get_time_once(rtc_date_time_t *date_time)
{
    RTC_DateTypeDef date = {0};
    RTC_TimeTypeDef time = {0};

    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);//必须在 GetTime 之后

    date_time->year = 2000 + date.Year;
    date_time->month = date.Month;
    date_time->day = date.Date;
    date_time->weekday = date.WeekDay;
    date_time->hour = time.Hours;
    date_time->minute = time.Minutes;
    date_time->second = time.Seconds;
}

void rtc_set_time(const rtc_date_time_t *date_time)
{
    rtc_date_time_t rtime;
    do {
        _rtc_set_time_once(date_time);
        HAL_Delay(5);
        _rtc_get_time_once(&rtime);
    } while (date_time->second != rtime.second);
}

void rtc_get_time(rtc_date_time_t *date_time)
{
    rtc_date_time_t time1, time2;
    do {
        _rtc_get_time_once(&time1);
        _rtc_get_time_once(&time2);
    } while (memcmp(&time1, &time2, sizeof(rtc_date_time_t)) != 0);

    memcpy(date_time, &time1, sizeof(rtc_date_time_t));
}
