/**
 * @file    delay.c
 * @brief   基于 SysTick 的高精度延时 / 计时模块（STM32F4 HAL 兼容实现）。
 */

#include "delay.h"
#include "stm32f4xx_hal.h"

static cpu_periodic_callback_t periodic_callback;
/* SysTick 原始节拍累加计数器（在 SysTick 中断中更新） */
volatile uint64_t cpu_tick_count;

/* HAL 的毫秒计数与节拍频率，由 stm32f4xx_hal.c 定义 */
extern __IO uint32_t uwTick;
extern HAL_TickFreqTypeDef uwTickFreq;

void cpu_tick_init(void)
{
    SysTick->LOAD = TICKS_PER_MS;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

uint64_t cpu_now(void)
{
    uint64_t now, last_count;
    do {
        last_count = cpu_tick_count;
        now = cpu_tick_count + SysTick->LOAD - SysTick->VAL;
    } while (last_count != cpu_tick_count);
    return now;
}

uint64_t cpu_get_us(void)
{
    return cpu_now() / TICKS_PER_US;
}

uint64_t cpu_get_ms(void)
{
    return cpu_now() / TICKS_PER_MS;
}

void cpu_delay_us(uint32_t us)
{
    uint64_t now = cpu_now();
    while (cpu_now() - now < (uint64_t)us * TICKS_PER_US);
}

void cpu_delay_ms(uint32_t ms)
{
    uint64_t now = cpu_now();
    while (cpu_now() - now < (uint64_t)ms * TICKS_PER_MS);
}

/*
 * 覆盖 HAL 的弱定义 HAL_IncTick()。
 * HAL 工程中的 SysTick_Handler（位于 stm32f4xx_it.c）会调用本函数，
 * 因此这里既维持 HAL 的毫秒计数 uwTick，又累加本模块的原始节拍计数，
 * 并每 1ms 调用一次注册的周期回调，
 * 从而在保证 HAL_Delay()/HAL_GetTick() 正常工作的同时，
 * 避免自定义 SysTick_Handler 与 HAL 工程中的同名中断服务函数发生重定义冲突。
 */
void HAL_IncTick(void)
{
    uwTick += uwTickFreq;
    cpu_tick_count += TICKS_PER_MS;

    if (periodic_callback)
        periodic_callback();
}

void cpu_register_periodic_callback(cpu_periodic_callback_t callback)
{
    periodic_callback = callback;
}
