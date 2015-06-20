#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x_conf.h"
#include "stm32f10x.h"


/*
6.2.4G:	CE:PA12			    gnd  vcc
		CSN:PA4		pa12---	ce   csn----pa4
		SCK:PA5		pa5----	sck  mosi---pa7
		MOSI:PA7	pa6----	miso irq----pa8
		MISO:PA6
		IRQ:PA8
*/

#define SPI_CE_H   GPIOA->BSRR = GPIO_Pin_12
#define SPI_CE_L   GPIOA->BRR = GPIO_Pin_12

#define SPI_CSN_H  GPIOA->BSRR = GPIO_Pin_4
#define SPI_CSN_L  GPIOA->BRR = GPIO_Pin_4

uint8_t SPI_RW(uint8_t dat);
void SPI1_Init(void);

#endif

