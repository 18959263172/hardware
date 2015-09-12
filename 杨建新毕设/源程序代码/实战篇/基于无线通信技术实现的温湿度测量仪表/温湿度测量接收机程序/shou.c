#include <reg52.h>
#include <intrins.h>

typedef unsigned char uchar;
typedef unsigned int uint;
uchar num;
sbit lcden=P3^7;
sbit lcdrs=P3^4;
sbit lcdrw=P3^6;
//****************************************NRF24L01�˿ڶ���***************************************
sbit 	MISO	=P1^4;
sbit 	MOSI	=P1^3;
sbit	SCK	    =P1^2;
sbit	CE	    =P1^0;
sbit	CSN		=P1^1;
sbit	IRQ		=P1^5;
//************************************����***************************************************
sbit	KEY1=P2^3;
sbit	KEY2=P2^4;
//************************************�����λѡ*********************************************
sbit	led1=P1^6;
sbit	led0=P1^7;
//************************************������***************************************************
sbit 	BELL=P2^7;
//***********************************�����0-9����*******************************************
                                                         //0~~9����
//*********************************************NRF24L01*************************************
#define TX_ADR_WIDTH    5   	// 5 uints TX address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  20  	// 20 uints TX payload
#define RX_PLOAD_WIDTH  20  	// 20 uints TX payload
uchar const TX_ADDRESS[TX_ADR_WIDTH]  = {0x35,0x43,0x10,0x10,0x03}	;//���ص�ַ
uchar const RX_ADDRESS[RX_ADR_WIDTH]= {0x35,0x43,0x10,0x10,0x03}; //���յ�ַ P1  ʵ�ʵ�ַΪ��03-10-10-43-35
//***************************************NRF24L01�Ĵ���ָ��*******************************************************
#define READ_REG        0x00  	// ���Ĵ���ָ��
#define WRITE_REG       0x20 	// д�Ĵ���ָ��
#define RD_RX_PLOAD     0x61  	// ��ȡ��������ָ��
#define WR_TX_PLOAD     0xA0  	// д��������ָ��
#define FLUSH_TX        0xE1 	// ��ϴ���� FIFOָ��
#define FLUSH_RX        0xE2  	// ��ϴ���� FIFOָ��
#define REUSE_TX_PL     0xE3  	// �����ظ�װ������ָ��
#define NOP             0xFF  	// ����
//*************************************SPI(nRF24L01)�Ĵ�����ַ****************************************************
#define CONFIG          0x00  // �����շ�״̬��CRCУ��ģʽ�Լ��շ�״̬��Ӧ��ʽ
#define EN_AA           0x01  // �Զ�Ӧ��������
#define EN_RXADDR       0x02  // �����ŵ�����
#define SETUP_AW        0x03  // �շ���ַ�������
#define SETUP_RETR      0x04  // �Զ��ط���������
#define RF_CH           0x05  // ����Ƶ������
#define RF_SETUP        0x06  // �������ʡ����Ĺ�������
#define STATUS          0x07  // ״̬�Ĵ���
#define OBSERVE_TX      0x08  // ���ͼ�⹦��
#define CD              0x09  // ��ַ���           
#define RX_ADDR_P0      0x0A  // Ƶ��0�������ݵ�ַ
#define RX_ADDR_P1      0x0B  // Ƶ��1�������ݵ�ַ
#define RX_ADDR_P2      0x0C  // Ƶ��2�������ݵ�ַ
#define RX_ADDR_P3      0x0D  // Ƶ��3�������ݵ�ַ
#define RX_ADDR_P4      0x0E  // Ƶ��4�������ݵ�ַ
#define RX_ADDR_P5      0x0F  // Ƶ��5�������ݵ�ַ
#define TX_ADDR         0x10  // ���͵�ַ�Ĵ���
#define RX_PW_P0        0x11  // ����Ƶ��0�������ݳ���
#define RX_PW_P1        0x12  // ����Ƶ��1�������ݳ���
#define RX_PW_P2        0x13  // ����Ƶ��2�������ݳ���
#define RX_PW_P3        0x14  // ����Ƶ��3�������ݳ���
#define RX_PW_P4        0x15  // ����Ƶ��4�������ݳ���
#define RX_PW_P5        0x16  // ����Ƶ��5�������ݳ���
#define FIFO_STATUS     0x17  // FIFOջ��ջ��״̬�Ĵ�������
//**************************************************************************************
void Delay(uint s);
void inerDelay_us(uchar n);
void init_NRF24L01(void);
uchar SPI_RW(uchar byte);
uchar SPI_Read(uchar reg);
//void SetRX_Mode(void);
uchar SPI_RW_Reg(uchar reg, uchar value);
uchar SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars);
uchar SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars);
uchar nRF24L01_RxPacket(uchar* rx_buf);
void nRF24L01_TxPacket(uchar * tx_buf);

void delay1ms(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}

void write_com(uchar com)
{
	lcdrs=0;
	P0=com;
	delay1ms(5);
	lcden=1;
	delay1ms(5);
	lcden=0;
}

void write_data(uchar date)
{
	lcdrs=1;
	P0=date;
	delay1ms(5);
	lcden=1;
	delay1ms(5);
	lcden=0;
}
void write_str(uchar *str)  
{  
 while(*str!='\0')  //δ����   
 {  
  write_data(*str++);  
  delay1ms(1);  
 }  
} 
void init_1602()
{	
	lcdrw=0;
	lcden=0;
	write_com(0x38);	
	write_com(0x0e);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
}
//*****************************************����ʱ*****************************************
void Delay(uint s)
{
	uint i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}
//******************************************************************************************
uchar 	bdata sta;   //״̬��־
sbit	RX_DR	=sta^6;
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;
/******************************************************************************************
/*��ʱ����
/******************************************************************************************/
void inerDelay_us(uchar n)
{
	for(;n>0;n--)
		_nop_();
}
//****************************************************************************************
/*NRF24L01��ʼ��
//***************************************************************************************/
void init_NRF24L01(void)
{
    inerDelay_us(100);
  CE=0;    // chip enable
  CSN=1;   // Spi disable 
  SCK=0;   // Spi clock line init high
 SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // д���ص�ַ 
 SPI_Write_Buf(WRITE_REG + RX_ADDR_P1, RX_ADDRESS, RX_ADR_WIDTH); // д���ն˵�ַ  P0


 SPI_RW_Reg(WRITE_REG + EN_AA,0x03);      //  Ƶ��0 - 5 �Զ� ACKӦ������ 
 SPI_RW_Reg(WRITE_REG + EN_RXADDR,0x03);  //  ������յ�ַƵ��0 - 5 
 SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   �����ŵ�����Ϊ2.4GHZ���շ�����һ��
 SPI_RW_Reg(WRITE_REG + RX_PW_P1, RX_PLOAD_WIDTH); //���ý������ݳ��ȣ���������ΪRX_PLOAD_WIDTH�ֽ�
 SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);     //���÷�������Ϊ1MHZ�����书��Ϊ���ֵ0dB

 CE=1;    // chip disable
}


/****************************************************************************************************
/*������uint SPI_RW(uint uchar)
/*���ܣ�NRF24L01��SPIдʱ��
/****************************************************************************************************/
uchar SPI_RW(uchar byte)
{
	uchar bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) // output 8-bit
   	{
		MOSI = (byte & 0x80);         // output 'uchar', MSB to MOSI
		byte = (byte << 1);           // shift next bit into MSB..
		SCK = 1;                      // Set SCK high..
		byte |= MISO;       		  // capture current MISO bit
		SCK = 0;            		  // ..then set SCK low again
   	}
    return(byte);           		  // return read uchar
}
/****************************************************************************************************
/*������uchar SPI_Read(uchar reg)
/*���ܣ�NRF24L01��SPIʱ��
/****************************************************************************************************/
uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	
	CSN = 0;                // CSN low, initialize SPI communication...
	SPI_RW(reg);            // Select register to read from..
	reg_val = SPI_RW(0);    // ..then read registervalue
	CSN = 1;                // CSN high, terminate SPI communication
	
	return(reg_val);        // return register value
}
/****************************************************************************************************/
/*���ܣ�NRF24L01��д�Ĵ�������
/****************************************************************************************************/
uchar SPI_RW_Reg(uchar reg, uchar value)
{
	uchar status;
	
	CSN = 0;                   // CSN low, init SPI transaction
	status = SPI_RW(reg);      // select register
	SPI_RW(value);             // ..and write value to it..
	CSN = 1;                   // CSN high again
	
	return(status);            // return nRF24L01 status uchar
}
/****************************************************************************************************/
/*������uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ���ڶ����ݣ�reg��Ϊ�Ĵ�����ַ��pBuf��Ϊ���������ݵ�ַ��uchars���������ݵĸ���
/****************************************************************************************************/
uchar SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uchar status,uchar_ctr;
	
	CSN = 0;                    		// Set CSN low, init SPI tranaction
	status = SPI_RW(reg);       		// Select register to write to and read status uchar
	
	for(uchar_ctr=0;uchar_ctr<uchars;uchar_ctr++)
		pBuf[uchar_ctr] = SPI_RW(0);    // 
	
	CSN = 1;                           
	
	return(status);                    // return nRF24L01 status uchar
}
/*********************************************************************************************************
/*������uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*����: ����д���ݣ�Ϊ�Ĵ�����ַ��pBuf��Ϊ��д�����ݵ�ַ��uchars��д�����ݵĸ���
/*********************************************************************************************************/
uchar SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uchar status,uchar_ctr;
	
	CSN = 0;            //SPIʹ��       
	status = SPI_RW(reg);   
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN = 1;           //�ر�SPI
	return(status);    // 
}
/****************************************************************************************************/
/*������void SetRX_Mode(void)
/*���ܣ����ݽ������� 
/****************************************************************************************************/
/*void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	CE = 1; 
	inerDelay_us(130);
}	*/
/******************************************************************************************************/
/*������unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*���ܣ����ݶ�ȡ�����rx_buf���ջ�������
/******************************************************************************************************/
uchar nRF24L01_RxPacket(uchar *rx_buf)
{	 
    uchar revale=0;
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0,RX_ADDRESS, RX_ADR_WIDTH);
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ�շ�����ж���Ӧ��16λCRC	��������
	CE = 1; 
	inerDelay_us(130);
	sta=SPI_Read(STATUS);     // ��ȡ״̬�Ĵ������ж����ݽ���״��
	if(RX_DR)				// �ж��Ƿ���յ�����
	{
	    CE = 0; 			//SPIʹ��
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,RX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//��ȡ������ɱ�־
						write_com(0x80);
						write_str("   Hum");
						write_data(':');
						write_data(rx_buf[1]/10%10+48);
						write_data(rx_buf[1]%10+48);
						
						write_data('%');
						write_com(0x80+0x40);
						write_str("   Tem");
						write_data(':');
						write_data(rx_buf[2]/10%10+48);
						write_data(rx_buf[2]%10+48);
                        write_data(0xdf);
						write_data('c');
				
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //���յ����ݺ�RX_DR,TX_DS,MAX_PT���ø�Ϊ1��ͨ��д1������жϱ�־
	return revale;
}
/***********************************************************************************************************
/*������void nRF24L01_TxPacket(unsigned char * tx_buf)
/*���ܣ����� tx_buf������
/**********************************************************************************************************/
void nRF24L01_TxPacket(uchar *tx_buf)
{
	CE=0;			//StandBy Iģʽ	
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // ����˵�ַ
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // װ������	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0e);   		 // IRQ�շ�����ж���Ӧ��16λCRC��������
	CE=1;		 //�ø�CE���������ݷ���
	inerDelay_us(20);	
}
//************************************������************************************************************
void main(void)
{		 
	uchar RxBuf[20]={0};	
	init_1602();
    init_NRF24L01() ;
	led0=1;led1=1;
		BELL=0;
		Delay(100);
		BELL=1;
	while(1)
	{	   
//***********************************************************************************************
//		SetRX_Mode();
		nRF24L01_RxPacket(RxBuf);	
		RxBuf[1] = 0x00;
		RxBuf[2] = 0x00;
	}
	
}
