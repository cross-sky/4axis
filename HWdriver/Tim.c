#include "config.h"

#define TASK_TICK_FREQ		1000//Hz 主任务频率


void TimerNvIC_Configuration(void)
{
	NVIC_InitTypeDef nvic_inits;

	nvic_inits.NVIC_IRQChannel = TIM3_IRQn;
	nvic_inits.NVIC_IRQChannelPreemptionPriority = 1; //定时器3作为串口打印定时器，优先级低于姿态解算
	nvic_inits.NVIC_IRQChannelSubPriority = 0;
	nvic_inits.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_inits);

	nvic_inits.NVIC_IRQChannel = TIM4_IRQn;
	nvic_inits.NVIC_IRQChannelPreemptionPriority = 0;// //定时器4作为姿态解算，优先级高于串口打印
	nvic_inits.NVIC_IRQChannelSubPriority = 0;
	nvic_inits.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_inits);
}


void TIM4_Init(uint8_t clock, uint16_t period)
{

	///TIM2,3,4:SystemClk=APB1(Max36Mhz)
	//PSC = 349 则     CK_CNT = 36Mhz/(349+1) =>10us
	// ARR = 50 000     1us * 50 000 =50ms
	//如果分频系数为TIM_CKD_DIV1时，TIMx的时钟就是APB1的时钟的两倍（72M）
	//Tout= ((arr+1)*(psc+1))/Tclk；
	//Tclk：TIM3的输入时钟频率（单位为Mhz）;Tout：TIM3溢出时间（单位为us）
	TIM_TimeBaseInitTypeDef tim_times;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_DeInit(TIM4);

	tim_times.TIM_Period = period -1;  //自动重载 ARR
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

	tim_times.TIM_Period = period;  //自动重载 ARR
	tim_times.TIM_Prescaler = clock - 1; // psc
	tim_times.TIM_ClockDivision = TIM_CKD_DIV1;//时钟分割?在未分频之前根据要求建立新的分频器，确定定时器，确定一定的延时时间
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

