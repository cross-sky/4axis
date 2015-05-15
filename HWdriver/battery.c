#include "config.h"

uint16_t adBuf[2];
uint8_t	adcDmaOK;
//BatteryCheck---->PB0

void BatteryCheckInit(void)
{	
	//忘了开dma中断优先级 nvic adc gpio dma 一个都不能少
	ADC_InitTypeDef		adcInits;
	DMA_InitTypeDef		dmaInits;
	GPIO_InitTypeDef	gpioInits;
	NVIC_InitTypeDef	nvicInits;

	RCC_APB2PeriphClockCmd(BATTERYADCclk | BATTERYPortCLK, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	gpioInits.GPIO_Pin = BATTERYPin;
	gpioInits.GPIO_Mode = GPIO_Mode_AIN;//模拟输入
//	gpioInits.GPIO_PuPd = GPIO_PuPd_NOPULL;//设置上下拉电阻
	GPIO_Init(BatteryPort, &gpioInits);

	DMA_DeInit( DMA1_Channel1);
	dmaInits.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	dmaInits.DMA_MemoryBaseAddr = (uint32_t)&adBuf;
	dmaInits.DMA_DIR = DMA_DIR_PeripheralSRC;//DMA转换模式为SRC模式，由外设搬移到内存
	dmaInits.DMA_BufferSize = 2;
	dmaInits.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//设备地址禁止后移(设置DMA的外设递增模式)
	dmaInits.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaInits.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dmaInits.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dmaInits.DMA_Mode = DMA_Mode_Normal;//循环模式开启，Buf写满后，自动回到初始地址开始传输
	dmaInits.DMA_Priority = DMA_Priority_Medium;
	dmaInits.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1,&dmaInits);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);////使能DMA传输完成中断

	//.........................................
	nvicInits.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	nvicInits.NVIC_IRQChannelPreemptionPriority = 2;
	nvicInits.NVIC_IRQChannelSubPriority = 2;
	nvicInits.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicInits);


	//扫描模式如果启用，则启动AD转换会转换所有设定的通道，如果是单次模式，则所有通道转换完成后不动作，如果是连续模式，则所有通道转换完成后继续从第一个通道开始转换
	adcInits.ADC_Mode = ADC_Mode_Independent;////独立工作模式
	adcInits.ADC_ScanConvMode = ENABLE;//扫描方式
	adcInits.ADC_ContinuousConvMode = DISABLE;////连续转换
	adcInits.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//由软件而不是外部触发启动
	adcInits.ADC_DataAlign = ADC_DataAlign_Right;
	adcInits.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &adcInits);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8,1,ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16,2, ADC_SampleTime_239Cycles5);

	/* Enable ADC1 DMA */
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));

	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{
		adcDmaOK = 1;
		DMA_ClearITPendingBit(DMA1_IT_TC1);
	}
}


//温度TEMP=(1.43-Vsense)/0.0043+25;
void AdcDmaTest(void)
{
	if (adcDmaOK == 1)
	{
		float ver = 3.3 / 4096;
		float tem1 = (1.43 - adBuf[1] * ver)/0.0043 + 25;
		adcDmaOK = 0;
		printf("voltage1 %.4f", adBuf[0]*ver);
		printf("tem %.4f..\r\n", tem1);
	}
}

