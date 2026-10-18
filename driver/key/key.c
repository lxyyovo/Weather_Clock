#include "stm32f4xx_hal.h"
#include "key.h"

// 定义两个按键 KEY0 PE4，KEY1 PE3
KEY_TypeDef key0 = {GPIOE, GPIO_PIN_4, 0, 0, 0};
KEY_TypeDef key1 = {GPIOE, GPIO_PIN_3, 0, 0, 0};

#define KEY_DEBOUNCE_TIME 20   // 消抖20ms，可调整

// 放在while(1)循环里不断调用
void key_scan(KEY_TypeDef *key)
{
    uint8_t level = HAL_GPIO_ReadPin(key->port, key->pin);
    uint32_t now = HAL_GetTick();

    switch(key->state)
    {
        case 0: // 空闲状态
            if(level == GPIO_PIN_RESET) //检测到低电平（按键按下）
            {
                key->tick = now;
                key->state = 1;
            }
            break;
        case 1: //消抖等待
            if(now - key->tick >= KEY_DEBOUNCE_TIME)
            {
                if(level == GPIO_PIN_RESET)
                {
                    key->state = 2;
                    key->press_flag = 1; //标记按键按下事件
                }
                else
                {
                    key->state = 0; //抖动，回到空闲
                }
            }
            break;
        case 2: //等待按键松开
            if(level == GPIO_PIN_SET)
            {
                key->state = 0;
            }
            break;
    }
}

// 获取按键按下标志，读一次自动清除标志
uint8_t key_getpress(KEY_TypeDef *key)
{
    uint8_t ret = key->press_flag;
    key->press_flag = 0;
    return ret;
}
