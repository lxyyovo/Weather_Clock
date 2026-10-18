#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "aht20.h"

/* AHT20 7 位地址 0x38，HAL 使用 8 位形式（左移一位）*/
#define AHT201_I2C_ADDR     0x70
/* HAL 阻塞收发超时（毫秒）*/
#define AHT201_I2C_TIMEOUT  100

/* 由 CubeMX 生成的 I2C1 句柄（PB6=SCL / PB7=SDA）*/
extern I2C_HandleTypeDef hi2c1;

static bool aht20_write(uint8_t data[], uint32_t length);
static bool aht20_read(uint8_t data[], uint32_t length);
static bool aht20_read_status(uint8_t *status);
static bool aht20_is_busy(void);
static bool aht20_is_ready(void);

bool aht20_init(void)
{
    HAL_Delay(40);
    if (aht20_is_ready())
        return true;

    if (!aht20_write((uint8_t[]){0xBE, 0x08, 0x00}, 3))
        return false;

    for (uint32_t t = 0; t < 100; t++)
    {
        HAL_Delay(1);
        if (aht20_is_ready())
            return true;
    }

    return false;
}

static bool aht20_write(uint8_t data[], uint32_t length)
{
    return HAL_I2C_Master_Transmit(&hi2c1, AHT201_I2C_ADDR, data,
                                   (uint16_t)length, AHT201_I2C_TIMEOUT) == HAL_OK;
}

static bool aht20_read(uint8_t data[], uint32_t length)
{
    return HAL_I2C_Master_Receive(&hi2c1, AHT201_I2C_ADDR, data,
                                  (uint16_t)length, AHT201_I2C_TIMEOUT) == HAL_OK;
}

static bool aht20_read_status(uint8_t *status)
{
    uint8_t cmd = 0x71;
    if (!aht20_write(&cmd, 1))
        return false;
    if (!aht20_read(status, 1))
        return false;

    return true;
}

static bool aht20_is_busy(void)
{
    uint8_t status;
    if (!aht20_read_status(&status))
        return false;
    return (status & 0x80) != 0;
}

static bool aht20_is_ready(void)
{
    uint8_t status;
    if (!aht20_read_status(&status))
        return false;
    return (status & 0x08) != 0;
}

bool aht20_start_measurement(void)
{
    return aht20_write((uint8_t[]){0xAC, 0x33, 0x00}, 3);
}

bool aht20_wait_for_measurement(void)
{
    for (uint32_t t = 0; t < 200; t++)
    {
        HAL_Delay(1);
        if (!aht20_is_busy())
            return true;
    }

    return false;
}

unsigned char CheckCrc8(unsigned char *pDat, unsigned char Lenth)
{
    unsigned char crc = 0xff, i, j;

    for (i = 0; i < Lenth; i++)
    {
        crc = crc ^ *pDat;
        for (j = 0; j < 8; j++)
        {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc <<= 1;
        }
        pDat++;
    }

    return crc;
}

bool aht20_read_measurement(float *temperature, float *humidity)
{
    uint8_t data[7];
    if (!aht20_read(data, 7))
        return false;

    if (CheckCrc8(data, 6) != data[6])
        return false;

    uint32_t raw_humidity = ((uint32_t)data[1] << 12) |
                            ((uint32_t)data[2] << 4) |
                            ((uint32_t)(data[3] & 0xF0) >> 4);
    uint32_t raw_temperature = ((uint32_t)(data[3] & 0x0F) << 16) |
                               ((uint32_t)data[4] << 8) |
                               ((uint32_t)data[5]);

    *humidity = (float)raw_humidity * 100.0f / (float)0x100000;
    *temperature = (float)raw_temperature * 200.0f / (float)0x100000 - 50.0f;

    return true;
}
