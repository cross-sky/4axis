#include "config.h"

uint16_t testflash[5]={1,2,3,4,5};

uint16_t sysTickFlag;

int main(void)
{
//	cycleCounter();	//获取时钟频率
	SysTick_Config(SystemCoreClock / 1000); ////SysTick开启系统tick定时器并初始化其中断，1ms
	TimerNvIC_Configuration();
	UART1_Init(BoundSet);
//	FLASH_Write(testflash);
//	FLASH_READ(testflash, 5);
//	if(FLASH_Write(STM32_FLASH_START, testflash, 5) == FLASH_WRITE_OK )  printf("write ok...");
	if(FLASH_READ(STM32_FLASH_START, testflash, 5) == FLASH_READ_OK ) printf("read ok...");
	
//	TIM_Init(); //暂不开启
	MotorInit();
//loadParamsFromEEPROM();//暂不开启
	BatteryCheckInit();
	IIC_Init();
	Mpu6050Init();
	MPU6050TestConnection();
	HMC5883_Init();

	while (1)
	{
		RTtest();
		AdcDmaTest();
		if (sysTickFlag > 10000 )
		{
			sysTickFlag = 0;
			DMA_Cmd(DMA1_Channel1, DISABLE);
			DMA1_Channel1->CNDTR = 2;
			DMA_Cmd(DMA1_Channel1, ENABLE);
			ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		}

		if(sysTickFlag % 1000 == 0 )
		{
			HMC5883_Test();
		}
	}

}


void SysTickHandler(void)
{
	sysTickFlag++;
}

