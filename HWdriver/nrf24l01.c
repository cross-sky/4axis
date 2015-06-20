#include "config.h"


uint8_t NRF24L01_RXDATA[RX_PLOAD_WIDTH];//nrf24l01���յ�������
uint8_t NRF24L01_TXDATA[RX_PLOAD_WIDTH];//nrf24l01��Ҫ���͵�����

uint8_t  RX_ADDRESS[RX_ADR_WIDTH]= {0x34,0xc3,0x10,0x10,0x00};	//���յ�ַ	

//д�Ĵ���
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

//���Ĵ���
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

//д������
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

//��������
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
	SPI_CE_L;////StandBy Iģʽ	
	NRF_WriteBuf(WR_TX_PLOAD, txbuf, len);
	SPI_CE_H;//�ø�CE���������ݷ���
}

//�ж�SPI�ӿ��Ƿ����NRFоƬ�Ƿ����
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

	if (i==5)   {printf("NRF24L01 is working...\r\n");return 1 ;}        //MCU ��NRF �ɹ����� 
	else        {printf("NRF24L01 wrong...\r\n");return 0 ;}        //MCU��NRF���������� 

}

uint8_t NRF24L01_RxPacket(uint8_t *rxbuf)
{
	uint8_t sta;//spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz�� 
	sta= NRF_ReadReg(NRFRegSTATUS);//��ȡ״̬�Ĵ�����ֵ 
	NRF_WriteReg(NRF_WRITE_REG+NRFRegSTATUS, sta);//���TX_DS��MAX_RT�жϱ�־
	if (sta & RX_OK)
	{
		NRF_ReadBuf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);//��ȡ����
		NRF_WriteReg(FLUSH_RX, 0xff);//���RX FIFO�Ĵ��� 
		return 1;
	}
	return 0;//û�յ��κ�����
}

void SetRxMode(void)
{
	SPI_CE_L;
	NRF_WriteReg(FLUSH_RX, 0xff);//���TX FIFO�Ĵ���	
	NRF_WriteBuf(NRF_WRITE_REG+RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);//дRX�ڵ��ַ
	NRF_WriteReg(NRF_WRITE_REG+EN_AA, 0x01);//ʹ��ͨ��0���Զ�Ӧ�� 
	NRF_WriteReg(NRF_WRITE_REG+EN_RXADDR, 0x01);//ʹ��ͨ��0�Ľ��յ�ַ 
	NRF_WriteReg(NRF_WRITE_REG+RF_CH, 40);//����RFͨ��Ƶ��		
	NRF_WriteReg(NRF_WRITE_REG+RX_PW_P0, RX_PLOAD_WIDTH);//ѡ��ͨ��0����Ч���ݿ�� 
	NRF_WriteReg(NRF_WRITE_REG+RF_SETUP, 0x0f);//����TX�������,0db����,2Mbps,���������濪��  
	NRF_WriteReg(NRF_WRITE_REG+CONFIG, 0x0f);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	SPI_CE_H;
	printf("nrf24l01 work on rx..\r\n");
}

void NRF24L01_Init(void)
{
	SPI1_Init();
	NRF24L01_Check();
	SetRxMode();
}
