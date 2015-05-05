#include "config.h"
#include "stm32f10x_flash.h"

FLASH_FLAG FLASHstatus;


void STMFLASH_Unlock(void)
{
	FLASH->KEYR=FLASH_KEY1;//д���������.
	FLASH->KEYR=FLASH_KEY2;
	printf("FLASH unlock...\r\n");
}

//flash����
void STMFLASH_Lock(void)
{
	FLASH->CR|=1<<7;//����
}

//�õ�FLASH״̬
uint8_t STMFLASH_GetStatus(void)
{	
	uint32_t res;		
	res=FLASH->SR; 
	if(res&(1<<0))return 1;		    //æ
	else if(res&(1<<2))return 2;	//��̴���
	else if(res&(1<<4))return 3;	//д��������
	return 0;						//�������
	
}

uint8_t FLASH_Write(uint16_t *memory)
{
	uint16_t t, count=0;
	RCC_HSICmd(ENABLE);
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(STM32_FLASH_START);
	t = sizeof((const char *)memory);
	while(count <= t)
	{
		FLASH_ProgramHalfWord((STM32_FLASH_START + count*2),*(memory+count));
		
		if(count > t)
		{
			FLASHstatus = FLASH_WRIKE_NO;
			return FLASHstatus;
		}
		count++;
	}
	FLASH_Lock();
	RCC_HSICmd(DISABLE);
	FLASHstatus = FLASH_WRITE_OK;
	return FLASHstatus;
}

uint8_t FLASH_READ(uint16_t *memory, uint16_t num)
{
	uint16_t count=0;
	while(count < num)
	{
		*(memory+count) = *(uint16_t *)(STM32_FLASH_START + count*2);
		printf("flash data %d",*(memory+count));
		
		if(count > num)
		{
			FLASHstatus = FLASH_READ_NO;
			return FLASHstatus;
		}
		count ++;
	}
	FLASHstatus = FLASH_READ_OK;
	return FLASHstatus;
}



