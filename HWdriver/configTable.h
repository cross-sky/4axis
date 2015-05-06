#ifndef __CONFIGTABLE_H
#define __CONFIGTABLE_H

#include "stm32f10x_conf.h"
#include "stm32f10x.h"


typedef struct 
{
	float version;
	float pidPitch[3];
	float pidPitchRate[3];
	float pidRoll[3];
	float pidRollRate[3];
	float pidYaw[3];
	float pidYawRate[3];
	float pidAlt[3];
	float pidAltVel[3];
	float accoOffset[3];
	float gyroOffset[3];
	float magOffset[3];
	float NRFaddr[5];
	float BTstate;
	float NRFmatchFlag;
}config_table_t;

extern config_table_t gtables;

#endif

