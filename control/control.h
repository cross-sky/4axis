#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x_conf.h"
#include "stm32f10x.h"

typedef struct
{
	float P;
	float I;
	float D;
	float Desired;
	float Error;
	float PreError;
	float PrePreError;
	float Increament;
	float Integ;
	float iLimit;
	float Deriv;
	float Output;
}PID_Typedef;



extern PID_Typedef pitch_angle_PID;
extern PID_Typedef pitch_rate_PID;

extern PID_Typedef roll_angle_PID;
extern PID_Typedef roll_rate_PID;

extern PID_Typedef yaw_angle_PID;
extern PID_Typedef yaw_rate_PID;

extern PID_Typedef alt_PID;
extern PID_Typedef alt_vel_PID;



#endif

