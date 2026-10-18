/**
 * @file    delay.h
 * @brief   基于 SysTick 的高精度延时 / 计时模块（STM32F4 HAL 兼容）。
 *          本文件集中声明该模块对外暴露的宏、全局变量与函数。
 */

#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f4xx_hal.h"

typedef void (*cpu_periodic_callback_t)(void);
/* 每个毫秒 / 微秒对应的 SysTick 原始节拍数（1 节拍 = 1 个内核时钟周期） */
#define TICKS_PER_MS    (SystemCoreClock / 1000U)
#define TICKS_PER_US    (SystemCoreClock / 1000000U)

/* SysTick 自启动以来累计的原始节拍数（单位：内核时钟周期），在 SysTick 中断中累加 */
extern volatile uint64_t cpu_tick_count;

/**
 * @brief  初始化 SysTick 定时器，使其每 1ms 产生一次中断。
 * @note   与 HAL_Init() 内部的默认配置一致；HAL 环境下通常无需重复调用。
 * @param  无
 * @return 无
 */
void cpu_tick_init(void);

/**
 * @brief  读取当前累计的 SysTick 原始节拍数。
 * @note   采用 64 位累加，避免 32 位计数器回绕导致的时间丢失。
 * @param  无
 * @return 自 SysTick 启动以来经过的内核时钟周期数
 */
uint64_t cpu_now(void);

/**
 * @brief  读取自 SysTick 启动以来经过的微秒数。
 * @param  无
 * @return 微秒计数（64 位）
 */
uint64_t cpu_get_us(void);

/**
 * @brief  读取自 SysTick 启动以来经过的毫秒数。
 * @param  无
 * @return 毫秒计数（64 位）
 */
uint64_t cpu_get_ms(void);

/**
 * @brief  阻塞式微秒级延时。
 * @param  us 需要延时的微秒数
 * @return 无
 */
void cpu_delay_us(uint32_t us);

/**
 * @brief  阻塞式毫秒级延时。
 * @param  ms 需要延时的毫秒数
 * @return 无
 */
void cpu_delay_ms(uint32_t ms);

/**
 * @brief  注册一个周期性回调函数，每 1ms 调用一次。
 * @param  callback 回调函数指针
 * @return 无
 */
void cpu_register_periodic_callback(cpu_periodic_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif /* DELAY_H */
