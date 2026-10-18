#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "wifi.h"
#include "esp32.h"
#include "page.h"

// WiFi初始化
void wifi_init(void)
{
    if(!esp_at_init())
    {
        printf("[AT] init failed\n");
        goto err;
    }
    printf("[AT] inited\n");

    if(!esp_at_wifi_init())
    {
        printf("[WiFi] init failed\n");
        goto err;
    }
    printf("[WiFi] inited\n");  

	if(!esp_at_sntp_init())
    {
        printf("[SNTP] init failed\n");
        goto err;   
    }
    printf("[SNTP] inited\n");  
    return;

err:
    //printf("[WIFI] init failed\n");
    error_page("wireless init failed");
    while (1)
    {
        ;//printf("AT Error\r\n");
        //HAL_Delay(1000);
    }
}

// WiFi等待连接
void wifi_wait_connect(void)
{
    printf("[WiFi] connecting\n");
    esp_at_connect_wifi(WIFI_SSID, WIFI_PASSWD, NULL);
    for(uint32_t t = 0; t < 10 * 1000; t += 100)
    {
        HAL_Delay(100);
        esp_wifi_info_t wifi_info = {0};
        if(esp_at_get_wifi_info(&wifi_info) && wifi_info.connected)
        {
            printf("[WiFi] connected\n");
            printf("[WIFI] SSID: %s, BSSID: %s, Channel: %d, RSSI: %d\n",
                wifi_info.ssid, wifi_info.bssid, wifi_info.channel, wifi_info.rssi);
            return;
        }
    }
    printf("[WiFi] connection timeout\n");
    error_page("wireless connect failed");
    while (1)
    {
        ;//printf("AT Error\r\n");
        //HAL_Delay(1000);
    }
}
