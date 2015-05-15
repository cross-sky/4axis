#include "config.h"


void delay_us(uint32_t nus)
{
	uint32_t t0 = micros();
	while(micros() - t0 < nus);
}

void delay_ms(uint32_t nms)
{
	uint32_t t0 = micros();
	while (micros() - t0 < nms * 1000);
}


