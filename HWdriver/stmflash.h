#ifndef __STMFLASH_H
#define __STMFLASH_H

#include "stm32f10x.h"

#define STM32_FLASH_SIZE  128//FLASH������С(��λΪK)
#define STM32_FLASH_WREN 	1       //ʹ��FLASHд��(0��������;1��ʹ��)

#define FLASH_PAGE_SIZE    ((uint16_t)0x400) //���һҳΪ1K��С

//#define STM32_FLASH_BASE	0x08000000 	//STM32 FLASH����ʼ��ַ
#define STM32_FLASH_START	 0x0801fc00 	//��Ϊ����Flash�����ʼ��ַ��ƫ����
//FLASH������ֵ
#define FLASH_KEY1               0X45670123
#define FLASH_KEY2               0XCDEF89AB



typedef enum {
	FLASH_WRITE_OK = 1,
	FLASH_WRIKE_NO = 0,
	FLASH_READ_OK = 1,
	FLASH_READ_NO = 0
}FLASH_FLAG ;


uint8_t FLASH_Write(uint16_t *memory);
uint8_t FLASH_READ(uint16_t *memory, uint16_t num);

#endif


