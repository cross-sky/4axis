#include "config.h"

uint16_t testflash[5]={1,2,3,4,5};

int main(void)
{
//	cycleCounter();	//��ȡʱ��Ƶ��
	SysTick_Config(SystemCoreClock / 1000); ////SysTick����ϵͳtick��ʱ������ʼ�����жϣ�1ms
	TimerNvIC_Configuration();
	UART1_Init(BoundSet);
//	FLASH_Write(testflash);
//	FLASH_READ(testflash, 5);
	if(FLASH_Write(STM32_FLASH_START, testflash, 5) == FLASH_WRITE_OK )  printf("write ok...");
	if(FLASH_READ(STM32_FLASH_START, testflash, 5) == FLASH_READ_OK ) printf("read ok...");
	
//	TIM_Init(); //�ݲ�����
	MotorInit();
//loadParamsFromEEPROM();//�ݲ�����

	while (1)
	{
		RTtest();
	}

}

