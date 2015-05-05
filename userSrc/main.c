#include "config.h"

uint16_t testflash[5]={1,2,3,4,5};

int main(void)
{
//	cycleCounter();	//获取时钟频率
	SysTick_Config(SystemCoreClock / 1000); ////SysTick开启系统tick定时器并初始化其中断，1ms
	TimerNvIC_Configuration();
	UART1_Init(BoundSet);
	FLASH_Write(testflash);
	FLASH_READ(testflash, 5);
	while (1)
	{
		RTtest();
	}

}

