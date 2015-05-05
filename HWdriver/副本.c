#include "config.h"



void main(void)
{
	cycleCounterInit();	//获取时钟频率
	SysTick_Config(SystemCoreClock / 1000); ////SysTick开启系统tick定时器并初始化其中断，1ms

}