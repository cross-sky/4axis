#include "config.h"


uint8_t buffer[14];

void Mpu6050Init(void)
{
	IICWriteByte(devAddr, MPU6050_RA_PWR_MGMT_1, 0x80);
	delay_ms(50);
	IICWriteByte(devAddr, MPU6050_RA_SMPLRT_DIV, 0x00);//SMPLRT_DIV = 0  Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
	IICWriteByte(devAddr, MPU6050_RA_PWR_MGMT_1, 0x03);//ʱ��ѡ��1-3Ϊ�����ǵ��κ�һ����
	IICWriteByte(devAddr, MPU6050_RA_INT_PIN_CFG, 1<<1);//I2C_BYPASS_EN//
	////���ٶ�44hz�˲���������42hz�˲�-���˽�ֹƵ�����ϵĲ���
	IICWriteByte(devAddr, MPU6050_RA_CONFIG, MPU6050_DLPF_BW_42);//default DLPF_CFG = 0 => ACC bandwidth = 260Hz  GYRO bandwidth = 256Hz)
	IICWriteByte(devAddr, MPU6050_RA_GYRO_CONFIG, 0x18);//������������� +-2000��ÿ��
	// Accel scale 8g (4096 LSB/g)
	IICWriteByte(devAddr, MPU6050_RA_USER_CTRL, 0x00);//�ر�I2C Master ģʽ
	IICWriteByte(devAddr, MPU6050_RA_ACCEL_CONFIG, 2<<3);
}

uint8_t MPU6050TestConnection(void)
{
	IICReadBytes(devAddr, MPU6050_RA_WHO_AM_I, 1, buffer);
	printf("who am i %d", buffer[0]);
	if (buffer[0] == 0x68)
		return 1;
	else
		return 0;
	
}
