#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "weather.h"

// 解析心知天气应答，提取城市、位置、天气、天气码和温度
bool parse_seniverse_response(const char *response, weather_info_t *info)
{
    //AT+HTTPCLIENT=2,1,"https://api.seniverse.com/v3/weather/now.json?key=SqBhSRMmPB7-70QzD&location=Shaoguan&language=en&unit=c",,,2
    //+HTTPCLIENT:274,{"results":[{"location":{"id":"WS2V1N2FZZ77","name":"Shaoguan","country":"CN","path":"Shaoguan,Shaoguan,Guangdong,China","timezone":"Asia/Shanghai","timezone_offset":"+08:00"},"now":{"text":"Foggy","code":"30","temperature":"27"},"last_update":"2026-09-20T23:04:11+08:00"}]}

    //OK
	response = strstr(response, "\"results\":");
	if (response == NULL)
		return false;
	
	const char *location_response = strstr(response, "\"location\":");
	if (location_response == NULL)
		return false;
	
	const char *location_name_response = strstr(location_response, "\"name\":");
	if (location_name_response)
	{
		sscanf(location_name_response, "\"name\": \"%31[^\"]\"", info->city);
	}
	
	const char *location_path_response = strstr(location_response, "\"path\":");
	if (location_path_response)
	{
		sscanf(location_path_response, "\"path\": \"%127[^\"]\"", info->location);
	}
	
	const char *now_response = strstr(response, "\"now\":");
	if (now_response == NULL)
		return false;
	
	const char *now_text_response = strstr(now_response, "\"text\":");
	if (now_text_response)
	{
		sscanf(now_text_response, "\"text\": \"%15[^\"]\"", info->weather);
	}
	
	const char *now_code_response = strstr(now_response, "\"code\":");
	if (now_code_response)
	{
		sscanf(now_code_response, "\"code\": \"%d\"", &info->weather_code);
	}
	
	char temperature_str[16] = { 0 };
	const char *now_temperature_response = strstr(now_response, "\"temperature\":");
	if (now_temperature_response)
	{
		if (sscanf(now_temperature_response, "\"temperature\": \"%15[^\"]\"", temperature_str) == 1)
			info->temperature = atof(temperature_str);
	}
	
	return true;
}
