#include "config.h"

uint16_t testflash[5]={1,2,3,4,5};

int main(void)
{
//	cycleCounter();	//��ȡʱ��Ƶ��
	SysTick_Config(SystemCoreClock / 1000); ////SysTick����ϵͳtick��ʱ������ʼ�����жϣ�1ms
	TimerNvIC_Configuration();
	UART1_Init(BoundSet);
	FLASH_Write(testflash);
	FLASH_READ(testflash, 5);
	while (1)
	{
		RTtest();
	}

}

