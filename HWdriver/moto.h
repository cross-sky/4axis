#ifndef __MOTO_H
#define __MOTO_H

#include "stm32f10x_conf.h"
#include "stm32f10x.h"

#define MOTORTIM		TIM2
#define MOTORTIM_CLK	RCC_APB1Periph_TIM2
#define MOTORTIM_GPIO	GPIOA
#define MOTORTIM_GPIOClk	RCC_APB2Periph_GPIOA
#define MOTORTIM_PIN	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3

#define MOTO_PwmMAX		999 
void MotorInit(void);
void MotorPwmFlash(int16_t moto1_pwm,int16_t moto2_pwm,int16_t moto3_pwm,int16_t moto4_pwm);

#endif

