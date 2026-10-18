#ifndef __AHT201_H__
#define __AHT201_H__

#include <stdbool.h>
#include <stdint.h>

bool aht20_init(void);
bool aht20_start_measurement(void);
bool aht20_wait_for_measurement(void);
bool aht20_read_measurement(float *temperature, float *humidity);

unsigned char CheckCrc8(unsigned char *pDat, unsigned char Lenth);

#endif /* __AHT201_H__ */
