#include "config.h"


uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH];//nrf24l01接收到的数据
uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH];//nrf24l01需要发送的数据

uint8_t  RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0xc3,0x10,0x10,0x00};	//接收地址	

//写寄存器
uint8_t NRF_WriteReg(uint8_t reg, uint8_t value)
{
	uint8_t dtemp;

	SPI_CE_L;//..........
	SPI_CSN_L;
	dtemp = SPI_RW(reg);
	SPI_RW(value);
	SPI_CSN_H;
	return dtemp;
}

//读寄存器
uint8_t NRF_ReadReg(uint8_t reg)
{
	uint8_t dtemp;

	SPI_CE_L;//.............
	SPI_CSN_L;
	SPI_RW(reg);
	dtemp = SPI_RW(0);
	SPI_CSN_H;
	return dtemp;
}

//写缓冲区
uint8_t NRF_WriteBuf(uint8_t reg, uint8_t *pbuf, uint8_t nchars)
{
	uint8_t i, dtemp;

	SPI_CE_L;//............
	SPI_CSN_L;
	dtemp = SPI_RW(reg);
	for (i=0; i<nchars; i++)
	{
		SPI_RW(pbuf[i]);
	}

	SPI_CSN_H;//add
	return dtemp;
}

//读缓冲区
uint8_t NRF_ReadBuf(uint8_t reg, uint8_t *pbuf, uint8_t nchars)
{
	uint8_t i, dtemp;

	SPI_CE_L;//............
	SPI_CSN_L;
	dtemp = SPI_RW(reg);
	for (i=0; i<nchars; i++)
	{
		pbuf[i]=SPI_RW(0);
	}

	SPI_CSN_H;//add
	return dtemp;
}

void NRF_TxPacket(uint8_t *txbuf, uint8_t len)
{
	SPI_CE_L;////StandBy I模式	
	NRF_WriteBuf(WR_TX_PLOAD, txbuf, len);
	SPI_CE_H;//置高CE，激发数据发送
}

//判断SPI接口是否接入NRF芯片是否可用
uint8_t NRF24L01_Check(void)
{
	uint8_t buf[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
	uint8_t buf1[5] = {0};
	uint8_t i;
	NRF_WriteBuf(NRF_WRITE_REG + TX_ADDR, buf, 5);
	NRF_ReadBuf(TX_ADDR, buf1, 5);

	for (i=0;i<5;i++) 
	{ 
		if (buf1[i]!=0xC2) 
			break; 
	} 

	if (i==5)   {printf("NRF24L01 is working...\r\n");return 1 ;}        //MCU 与NRF 成功连接 
	else        {printf("NRF24L01 wrong...\r\n");return 0 ;}        //MCU与NRF不正常连接 

}

uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;//spi速度为9Mhz（24L01的最大SPI时钟为10Mhz） 
	sta= NRF_ReadReg(NRFRegSTATUS);//读取状态寄存器的值 
	NRF_WriteReg(NRF_WRITE_REG+NRFRegSTATUS, sta);//清除TX_DS或MAX_RT中断标志
	if (sta & RX_OK)
	{
		NRF_ReadBuf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);//读取数据
		NRF_WriteReg(FLUSH_RX, 0xff);//清除RX FIFO寄存器 
		return 1;
	}
	return 0;//没收到任何数据
}

void SetRxMode(void)
{
	SPI_CE_L;
	NRF_WriteReg(FLUSH_RX, 0xff);//清除TX FIFO寄存器	
	NRF_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);//写RX节点地址
	NRF_WriteReg(NRF_WRITE_REG+EN_AA, 0x01);//使能通道0的自动应答 
	NRF_WriteReg(NRF_WRITE_REG+EN_RXADDR, 0x01);//使能通道0的接收地址 
	NRF_WriteReg(NRF_WRITE_REG+RF_CH, 40);//设置RF通信频率		
	NRF_WriteReg(NRF_WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 
	NRF_WriteReg(NRF_WRITE_REG+RF_SETUP, 0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启  
	NRF_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	SPI_CE_H;
	printf("nrf24l01 work on rx..\r\n");
}

void NRF24L01_Init(void)
{
	SPI1_Init();
	NRF24L01_Check();
	SetRxMode();
}
