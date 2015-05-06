#include "config.h"

//tim2 pa.0, pa.1,pa.2,pa.3
//即初始化定时器2为PWM输出模式 24khz
void MotorInit(void)
{
	GPIO_InitTypeDef		gpio_inits;
	TIM_TimeBaseInitTypeDef tim_inits;
	TIM_OCInitTypeDef		tim_ocinits;

	uint16_t prescalerValues = 0;
	RCC_APB2PeriphClockCmd(MOTORTIM_GPIOClk, ENABLE);
	RCC_APB1PeriphClockCmd(MOTORTIM_CLK, ENABLE);

	gpio_inits.GPIO_Pin = MOTORTIM_PIN;
	gpio_inits.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_inits.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(MOTORTIM_GPIO, &gpio_inits);

	TIM_DeInit(MOTORTIM);

	prescalerValues = (uint16_t)(SystemCoreClock / 24000000) -1;

	tim_inits.TIM_Period = 999;
	tim_inits.TIM_Prescaler = prescalerValues;
	tim_inits.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_inits.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(MOTORTIM,&tim_inits);

	tim_ocinits.TIM_OCMode = TIM_OCMode_PWM1;
	tim_ocinits.TIM_OutputState = TIM_OutputState_Enable;
	tim_ocinits.TIM_Pulse = 100;//脉冲宽度
	tim_ocinits.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(MOTORTIM,&tim_ocinits );
	TIM_OC2Init(MOTORTIM,&tim_ocinits);
	TIM_OC3Init(MOTORTIM, &tim_ocinits);
	TIM_OC4Init(MOTORTIM, &tim_ocinits);

	TIM_OC1PreloadConfig(MOTORTIM, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(MOTORTIM, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(MOTORTIM, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(MOTORTIM, TIM_OCPreload_Enable);

	TIM_Cmd(MOTORTIM, ENABLE);

	printf("motor on....ing \r\n");
}

 
void MotorPwmFlash(int16_t moto1_pwm,int16_t moto2_pwm,int16_t moto3_pwm,int16_t moto4_pwm)
{
	if(moto1_pwm > MOTO_PwmMAX) moto1_pwm = MOTO_PwmMAX;
	if(moto2_pwm > MOTO_PwmMAX) moto2_pwm = MOTO_PwmMAX;
	if(moto3_pwm > MOTO_PwmMAX) moto3_pwm = MOTO_PwmMAX;
	if(moto4_pwm > MOTO_PwmMAX) moto4_pwm = MOTO_PwmMAX;

	if(moto1_pwm <= 0 ) moto1_pwm = 0;
	if(moto2_pwm <= 0 ) moto2_pwm = 0;
	if(moto3_pwm <= 0 ) moto3_pwm = 0;
	if(moto4_pwm <= 0 ) moto4_pwm = 0;

	MOTORTIM->CCR1 = moto1_pwm;
	MOTORTIM->CCR2 = moto2_pwm;
	MOTORTIM->CCR3 = moto3_pwm;
	MOTORTIM->CCR4 = moto4_pwm;

}
