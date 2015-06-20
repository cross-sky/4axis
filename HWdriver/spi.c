#include "config.h"

void SPI1_Init(void)
{
	SPI_InitTypeDef sspiInits;
	GPIO_InitTypeDef sgpioInits;
	//maybe usefull to add rcc_aifo ,the fact is whether rcc_afio on or off it does not affect spi1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE);
	//|RCC_APB2Periph_AFIO
	sgpioInits.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	sgpioInits.GPIO_Speed = GPIO_Speed_10MHz;
	sgpioInits.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &sgpioInits);

	//IRQ:PA8 CSN:PA4 CE:PA12
	sgpioInits.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_12;
	sgpioInits.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &sgpioInits);

	sgpioInits.GPIO_Pin = GPIO_Pin_8;
	sgpioInits.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &sgpioInits);


	SPI_CSN_H;//CSN:PA4
	//SPI_CE_L;//.............
	sspiInits.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	sspiInits.SPI_Mode = SPI_Mode_Master;
	sspiInits.SPI_DataSize = SPI_DataSize_8b;
	sspiInits.SPI_CPOL = SPI_CPOL_Low;//
	sspiInits.SPI_CPHA = SPI_CPHA_1Edge;
	sspiInits.SPI_NSS = SPI_NSS_Soft;
	sspiInits.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	sspiInits.SPI_FirstBit = SPI_FirstBit_MSB;
	sspiInits.SPI_CRCPolynomial = 7;//CRC值计算的多项式
	SPI_Init(SPI1, &sspiInits);

	SPI_Cmd(SPI1, ENABLE);
	printf("spi  ing....\r\n");
}


uint8_t SPI_RW(uint8_t dat)
{
	uint8_t retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
	{
		retry++;
		if (retry > 100)
			return 0;
	}
	SPI_I2S_SendData(SPI1, dat);
	retry=0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
	{
		retry++;
		if (retry > 100)
			return 0;
	}
	return SPI_I2S_ReceiveData(SPI1);
}

