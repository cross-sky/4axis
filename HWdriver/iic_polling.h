#ifndef __IIC_POLLING_H
#define __IIC_POLLING_H

#include "stm32f10x_conf.h"
#include "stm32f10x.h"


#define SDA_H GPIOB->BSRR = GPIO_Pin_5
#define SDA_L GPIOB->BRR = GPIO_Pin_5

#define SCL_H GPIOB->BSRR = GPIO_Pin_6
#define SCL_L GPIOB->BRR = GPIO_Pin_6

#define SDA_READ (GPIOB->IDR & GPIO_Pin_5)

typedef enum {FALSE = 0, TRUE = 1} bool;

uint8_t IICWriteByte(uint8_t dev, uint8_t reg, uint8_t data);
uint8_t IICReadByte(uint8_t dev, uint8_t reg, uint8_t *dat);
uint8_t IICWriteBytes(uint8_t dev, uint8_t reg, uint8_t length,uint8_t *data);
uint8_t IICReadBytes(uint8_t dev, uint8_t reg, uint8_t length, uint8_t *data);
uint8_t I2C_ReadOneByte(uint8_t I2C_Addr, uint8_t reg_addr);
void IIC_Init(void);

#endif

