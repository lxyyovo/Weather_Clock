#ifndef _key_h
#define _key_h

#include "stm32f4xx_hal.h"

// 按键状态结构体，非阻塞状态机
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
    uint32_t tick;        // 记录时间戳
    uint8_t state;        // 状态 0空闲 1消抖等待 2确认按下
    uint8_t press_flag;   // 按下标志，读取后清零
} KEY_TypeDef;

void key_scan(KEY_TypeDef *key);
uint8_t key_getpress(KEY_TypeDef *key);


#endif
