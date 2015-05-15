#include "config.h"

int16_t HMC5883_Fifo[3][11];
//float HMC5883_lastx,HMC5883_lasty,HMC5883_lastz;


void HMC5883_GetId(uint8_t *id)
{
	id[0] = I2C_ReadOneByte(HMC58X3_ADDR, HMC58X3_R_IDA);
	id[1] = I2C_ReadOneByte(HMC58X3_ADDR, HMC58X3_R_IDB);
	id[2] = I2C_ReadOneByte(HMC58X3_ADDR, HMC58X3_R_IDC);

}

void HMC5883_Check(void)
{
	uint8_t ID_temp[3];
	HMC5883_GetId(ID_temp);

	if( (ID_temp[0]==0x48) && (ID_temp[1]==0x34) && (ID_temp[2]==0x33) )
		printf("hmc5883l found...\r\n");
	else
		printf("hmc5883l not found...\r\n");

}

void HMC5883_writeReg(uint8_t reg, uint8_t val)
{
	IICWriteByte(HMC58X3_ADDR, reg, val);
}

void HMC5883_setMode(uint8_t mod)
{
	if (mod > 2)
	{
		return;
	}

	HMC5883_writeReg(HMC58X3_R_MODE, mod);
	delay_us(100);
}



void HMC5883_newValue(int16_t x, int16_t y, int16_t z)
{
	uint8_t  j;
	static uint8_t i=0;
	int32_t sum = 0;

	i=i%10;
	HMC5883_Fifo[0][i] = x;
	HMC5883_Fifo[1][i] = y;
	HMC5883_Fifo[2][i] = z;
	i++;

	for (j=0; j<10; j++)
	{
		sum += HMC5883_Fifo[0][j];
	}
	HMC5883_Fifo[0][10] = sum /10;

	sum=0;
	for (j=0; j<10; j++)
	{
		sum += HMC5883_Fifo[1][j];
	}
	HMC5883_Fifo[1][10] = sum /10;

	sum=0;
	for (j=0; j<10; j++)
	{
		sum += HMC5883_Fifo[2][j];
	}
	HMC5883_Fifo[2][10] = sum /10;

}

void HMC5883_GetRaw(int16_t *x, int16_t *y, int16_t *z)
{
	uint8_t vbuff[6]={0};
	IICReadBytes(HMC58X3_ADDR, HMC58X3_R_XM, 6, vbuff);
	HMC5883_newValue( ((int16_t)vbuff[0]<<8 | vbuff[1]), ((int16_t)vbuff[2]<<8 | vbuff[3]), ((int16_t)vbuff[4]<<8 | vbuff[5]) );
	*x = HMC5883_Fifo[0][10];
	*y = HMC5883_Fifo[1][10];
	*z = HMC5883_Fifo[2][10];
}

void HMC5883_FifoInit(void)
{
	int16_t temp[3];
	uint8_t i;
	for (i=0; i<20; i++)
	{
		HMC5883_GetRaw(&temp[0], &temp[1], &temp[2]);
		delay_us(200);
	}
}

void HMC5883_Test(void)
{
	int16_t temp[3];
	HMC5883_GetRaw(&temp[0], &temp[1], &temp[2]);
	printf("-x:%d -y:%d -z:%d..\r\n", temp[0], temp[1], temp[2]);
}

void HMC5883_Init(void)
{
	HMC5883_Check();
	HMC5883_writeReg(HMC58X3_R_CONFA, 0x78);//采样平均数8;数据输出速率15hz
	HMC5883_writeReg(HMC58X3_R_CONFB, 0xa0);//增益4.7Ga
	HMC5883_writeReg(HMC58X3_R_MODE, 0x00);
	HMC5883_FifoInit();
}

