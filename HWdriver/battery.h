#ifndef __BATTERY_H
#define __BATTERY_H

#include "stm32f10x_conf.h"
#include "stm32f10x.h"

#define BatteryPort	GPIOB
#define BATTERYPin	GPIO_Pin_0
#define BATTERYPortCLK	RCC_APB2Periph_GPIOB
#define BATTERYADCclk	RCC_APB2Periph_ADC1

void BatteryCheckInit(void);
void AdcDmaTest(void);
void DMA1_Channel1_IRQHandler(void);

#endif

