#include "config.h"



void main(void)
{
	cycleCounterInit();	//��ȡʱ��Ƶ��
	SysTick_Config(SystemCoreClock / 1000); ////SysTick����ϵͳtick��ʱ������ʼ�����жϣ�1ms

}