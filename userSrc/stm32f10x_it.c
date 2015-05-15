/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"


static volatile uint32_t usTicks = 0;
volatile uint32_t sysTickUptime = 0;

extern void SysTickHandler(void);
/** @addtogroup STM32F10x_StdPeriph_Template;
=======
extern void time_delay_decrement( void );*/
/** @addtogroup STM32F10x_StdPeriph_Template;
>>>>>>> 335796abe5a527f8f02456764720a4efa9dfba1f
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
//	TPCRemarks(TaskComps);
	SysTickHandler();
	sysTickUptime++;
}

uint8_t cycleCounter(void)
{
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq(&clocks);
	return usTicks = clocks.SYSCLK_Frequency / 1000000;

}

//return system uptime in microseconds
uint32_t micros(void)
{
	register uint32_t ms, cycle_cnt;
	do 
	{
		ms = sysTickUptime;
		cycle_cnt = SysTick->VAL;
	} while (ms != sysTickUptime);

	return ms * 1000 + (72000 - cycle_cnt)/72;
}

//return system uptime in milliseconds
uint32_t millis(void)
{
	return sysTickUptime;
}
void EXTI9_5_IRQHandler(void)
{					////ȷ���Ƿ������EXTI Line�ж�.;	
// 	if ( EXTI_GetITStatus( EXTI_Line7 ) != RESET )
// 	{
// 
// 		GPIO_WriteBit( GPIOC, GPIO_Pin_3,
// 			( BitAction)( (1-GPIO_ReadOutputDataBit( GPIOC, GPIO_Pin_3))));
// 
// 				
// 		EXTI_ClearITPendingBit( EXTI_Line7 );
// 
// 
// 	}

	
}


//void USART1_IRQHandler( void )
//{
	
// 	if ( USART_GetITStatus( USART1, USART_IT_RXNE) != RESET)
// 	{
// 		USART_ClearITPendingBit( USART1, USART_IT_RXNE);
// 		usart1_buf[ usart1_rx] = USART_ReceiveData( USART1);
// 		usart1_rx++;
// 		usart1_rx &= 0xff;

// 	}
// 	//ͷ;
// 	if ( usart1_buf[usart1_rx - 1 ] == 0xf0 )
// 	{
// 		usart1_tx = usart1_rx - 1;
// 	}
// 	//��⵽ͷ������¼�⵽β;
// 	if ( ( usart1_buf[usart1_tx] == 0xf0) && ( usart1_buf[usart1_rx -1] == 0x0f))
// 	{
// 		usart1_len = usart1_rx -1 - usart1_tx;  //���� ;
// 		usart1_sta = 1;   //��־λ  ;
// 	}

// 	if ( USART_GetFlagStatus( USART1,USART_FLAG_ORE) == SET ) //���;
// 	{
// 		USART_ClearFlag( USART1,USART_FLAG_ORE);  //��SR;
// 		USART_ReceiveData( USART1);  //��DR 
// 	}

//}

/*
void DMA1_Channel7_IRQHandler(void)
{
	u8 i;
	extern u16 i2c_rx_buf[14]; 
	extern int16_t accel_gyro[7];

	if(DMA_GetFlagStatus(DMA1_FLAG_TC7))
	{
		DMA_ClearFlag(DMA1_FLAG_TC7);

		I2C_DMACmd( MPU6050_I2C, DISABLE);
		I2C_GenerateSTOP(MPU6050_I2C, ENABLE);

		DMA_Cmd(MPU6050_DMA_CHANNEL, DISABLE);

		for (i=0; i<7; i++)
		{
			accel_gyro[i] = (int16_t)( (u16)i2c_rx_buf[2*i]<<8 + i2c_rx_buf[2*i + 1]);

		}

	}

}
*/

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
