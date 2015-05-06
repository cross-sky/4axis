#include "config.h"


#define TABLE_ADDRESS STM32_FLASH_START

config_table_t gtables;////用来存放EEPROM列表上的存放的参数变量的信息
uint8_t gParamsSaveRRPROMRequest = 0;////请求保存参数到EEPROM的信号量

#define EEPROM_DEFAULT_VERSION 1.0f

static uint8_t isEEPROMValid(void)
{
	FLASH_READ(TABLE_ADDRESS, (uint16_t *)(&gtables), 2);
	if (gtables.version == EEPROM_DEFAULT_VERSION)
		return 1;
	else
		return 0;
}

void tableReadEEPROM(void)
{
	uint16_t paramNum = sizeof(gtables)/sizeof(float);
	FLASH_READ(TABLE_ADDRESS, (uint16_t *)(&gtables), paramNum*2);

}

void tableWriteEEPROM(void)
{
	uint16_t paramNum = sizeof(gtables)/sizeof(float);
	FLASH_Write(TABLE_ADDRESS, (uint16_t *)(&gtables), paramNum*2);
}



void TableToParam(void)
{
	uint8_t i;
	for (i=0; i<3; i++)
	{
		((float *)(&pitch_angle_PID))[i] = ((float *)(&gtables.pidPitch))[i];
		((float *)(&roll_angle_PID))[i]=((float *)(&gtables.pidRoll))[i];
		((float *)(&yaw_angle_PID))[i]=((float *)(&gtables.pidYaw))[i];

		((float *)(&pitch_rate_PID))[i]=((float *)(&gtables.pidPitchRate))[i];
		((float *)(&roll_rate_PID))[i]=((float *)(&gtables.pidRollRate))[i];
		((float *)(&yaw_rate_PID))[i]=((float *)(&gtables.pidYawRate))[i];

		((float *)(&alt_PID))[i]=((float *)(&gtables.pidAlt))[i];
		((float *)(&alt_vel_PID))[i]=((float *)(&gtables.pidAltVel))[i];

		//......................
// 		imu.accOffset[i]=gtables.accOffset[i];
// 		imu.gyroOffset[i]=gtables.gyroOffset[i];
// 
// 
// 
// #ifdef NEW_ATTI_CTRL
// 		AttiCtrlParamsFromPIDTable();	//load to new ctrl param
// #endif

	}

// 	for(i=0;i<5;i++)
// 		((u8 *)(&RX_ADDRESS))[i] = ((float *)(&gtables.NRFaddr))[i];

// 	BTstate = gtables.BTstate;
// 	NRFMatched = gtables.NRFmatchFlag;

}

void ParamToTable(void)
{
	uint8_t i=0;
//	float temp;
	for(i=0;i<3;i++)
	{
		((float *)(&gtables.pidPitch))[i]=((float *)(&pitch_angle_PID))[i];
//		temp=((float *)(&roll_angle_PID))[i];
//		*((float *)(&table.pidRoll) + i) =  ((float *)(&roll_angle_PID))[i];
		((float *)(&gtables.pidRoll))[i]=((float *)(&roll_angle_PID))[i];
		((float *)(&gtables.pidYaw))[i]=((float *)(&yaw_angle_PID))[i];

		((float *)(&gtables.pidPitchRate))[i]=((float *)(&pitch_rate_PID))[i];
		((float *)(&gtables.pidRollRate))[i]=((float *)(&roll_rate_PID))[i];
		((float *)(&gtables.pidYawRate))[i]=((float *)(&yaw_rate_PID))[i];

		((float *)(&gtables.pidAlt))[i]=((float *)(&alt_PID))[i];
		((float *)(&gtables.pidAltVel))[i]=((float *)(&alt_vel_PID))[i];


// 		gtables.accOffset[i]=imu.accOffset[i];
// 		gtables.gyroOffset[i]=imu.gyroOffset[i];
	}

// 	for(i=0;i<5;i++)
// 		((float *)(&gtables.NRFaddr))[i] = ((u8 *)(&RX_ADDRESS))[i];
// 
// 
// 	gtables.BTstate = BTstate;
// 	gtables.NRFmatchFlag = NRFMatched;


}


void loadParamsFromEEPROM(void)
{
	if (isEEPROMValid())
	{
		tableReadEEPROM();
		TableToParam();
	}
	else
	{
		tableWriteEEPROM();
		ParamToTable();

	}
}
