#include "config.h"

#define TASK_TICK_FREQ		1000//Hz ������Ƶ��


void TimerNvIC_Configuration(void)
{
	NVIC_InitTypeDef nvic_inits;

	nvic_inits.NVIC_IRQChannel = TIM3_IRQn;
	nvic_inits.NVIC_IRQChannelPreemptionPriority = 1; //��ʱ��3��Ϊ���ڴ�ӡ��ʱ�������ȼ�������̬����
	nvic_inits.NVIC_IRQChannelSubPriority = 0;
	nvic_inits.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_inits);

	nvic_inits.NVIC_IRQChannel = TIM4_IRQn;
	nvic_inits.NVIC_IRQChannelPreemptionPriority = 0;// //��ʱ��4��Ϊ��̬���㣬���ȼ����ڴ��ڴ�ӡ
	nvic_inits.NVIC_IRQChannelSubPriority = 0;
	nvic_inits.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_inits);
}


void TIM4_Init(uint8_t clock, uint16_t period)
{

	///TIM2,3,4:SystemClk=APB1(Max36Mhz)
	//PSC = 349 ��     CK_CNT = 36Mhz/(349+1) =>10us
	// ARR = 50 000     1us * 50 000 =50ms
	//�����Ƶϵ��ΪTIM_CKD_DIV1ʱ��TIMx��ʱ�Ӿ���APB1��ʱ�ӵ�������72M��
	//Tout= ((arr+1)*(psc+1))/Tclk��
	//Tclk��TIM3������ʱ��Ƶ�ʣ���λΪMhz��;Tout��TIM3���ʱ�䣨��λΪus��
	TIM_TimeBaseInitTypeDef tim_times;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_DeInit(TIM4);

	tim_times.TIM_Period = period -1;  //�Զ����� ARR
	tim_times.TIM_Prescaler = clock - 1; // psc
	tim_times.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_times.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &tim_times);
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	printf("tim4 begian...\r\n");
}

void TIM3_Init(uint8_t clock, uint16_t period)
{

	TIM_TimeBaseInitTypeDef tim_times;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_DeInit(TIM3);

	tim_times.TIM_Period = period;  //�Զ����� ARR
	tim_times.TIM_Prescaler = clock - 1; // psc
	tim_times.TIM_ClockDivision = TIM_CKD_DIV1;//ʱ�ӷָ�?��δ��Ƶ֮ǰ����Ҫ�����µķ�Ƶ����ȷ����ʱ����ȷ��һ������ʱʱ��
	tim_times.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3, &tim_times);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	printf("tim3 begian...\r\n");
}

void TIM_Init(void)
{
	TIM3_Init(72, 1000);
	TIM4_Init(72, 1000);

}

