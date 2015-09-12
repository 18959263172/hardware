///无线模块板
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
 //*********************************************NRF24L01*************************************
#define TX_ADR_WIDTH    5   	// 5 uints TX address width
#define RX_ADR_WIDTH    5   	// 5 uints RX address width
#define TX_PLOAD_WIDTH  20  	// 20 uints TX payload
#define RX_PLOAD_WIDTH  20  	// 20 uints TX payload

uchar const TX_ADDRESS[TX_ADR_WIDTH]= {0x35,0x43,0x10,0x10,0x03}; 	//本地地址
uchar const RX_ADDRESS[RX_ADR_WIDTH]= {0x35,0x43,0x10,0x10,0x03};	//接收地址
//***************************************NRF24L01寄存器指令*******************************************************
#define READ_REG        0x00  	// 读寄存器指令
#define WRITE_REG       0x20 	// 写寄存器指令
#define RD_RX_PLOAD     0x61  	// 读取接收数据指令
#define WR_TX_PLOAD     0xA0  	// 写待发数据指令
#define FLUSH_TX        0xE1 	// 冲洗发送 FIFO指令
#define FLUSH_RX        0xE2  	// 冲洗接收 FIFO指令
#define REUSE_TX_PL     0xE3  	// 定义重复装载数据指令
#define NOP             0xFF  	// 保留
//*************************************SPI(nRF24L01)寄存器地址****************************************************
#define CONFIG          0x00  // 配置收发状态，CRC校验模式以及收发状态响应方式
#define EN_AA           0x01  // 自动应答功能设置
#define EN_RXADDR       0x02  // 可用信道设置
#define SETUP_AW        0x03  // 收发地址宽度设置
#define SETUP_RETR      0x04  // 自动重发功能设置
#define RF_CH           0x05  // 工作频率设置
#define RF_SETUP        0x06  // 发射速率、功耗功能设置
#define STATUS          0x07  // 状态寄存器
#define OBSERVE_TX      0x08  // 发送监测功能
#define CD              0x09  // 地址检测           
#define RX_ADDR_P0      0x0A  // 频道0接收数据地址
#define RX_ADDR_P1      0x0B  // 频道1接收数据地址
#define RX_ADDR_P2      0x0C  // 频道2接收数据地址
#define RX_ADDR_P3      0x0D  // 频道3接收数据地址
#define RX_ADDR_P4      0x0E  // 频道4接收数据地址
#define RX_ADDR_P5      0x0F  // 频道5接收数据地址
#define TX_ADDR         0x10  // 发送地址寄存器
#define RX_PW_P0        0x11  // 接收频道0接收数据长度
#define RX_PW_P1        0x12  // 接收频道1接收数据长度
#define RX_PW_P2        0x13  // 接收频道2接收数据长度
#define RX_PW_P3        0x14  // 接收频道3接收数据长度
#define RX_PW_P4        0x15  // 接收频道4接收数据长度
#define RX_PW_P5        0x16  // 接收频道5接收数据长度
#define FIFO_STATUS     0x17  // FIFO栈入栈出状态寄存器设置
//**************************************************************************************

//ds18b20
sbit DQ=P2^0;			 
// 1602
sbit lcdrs=P3^4;
sbit lcdrw=P3^6;
sbit lcden=P3^7;
sbit BELL=P1^6;
//24l01
sbit 	MISO	=P1^4;
sbit 	MOSI	=P1^3;
sbit	SCK	    =P1^2;
sbit	CE	    =P1^0;
sbit	CSN		=P1^1;
sbit	IRQ		=P1^5;
uint wendu=0;
////////  1602
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
 while(*str!='\0')  //未结束   
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
/////	 ////			 ds18b20

bit init_DS18B20()
{ 
	uchar num;
	bit flag;
	DQ=1;
	for(num=0;num<2;num++);  //先拉高
	DQ=0;
	for(num=0;num<200;num++);  // 480-960us	powerup
	DQ=1;
	for(num=0;num<20;num++);	//  >60us   wait
	flag=DQ;					// 响应
	for(num=0;num<150;num++);	//	 60-240us ds18b20存在信号
	DQ=1;
	return flag;
}

void DS18B20_WR_CHAR(uchar byte)	// 先写低位
{	
	uchar num;
	uchar num1;
	for(num1=0;num1<8;num1++)
	{	 	
		DQ=0;		//拉低
		_nop_();	//下拉1us
		_nop_();
		DQ=byte&0x01;
		for(num=0;num<20;num++);	//  >60us   wait
		byte>>=1;	
		DQ=1;	  //拉高	
		_nop_();
		_nop_();
	}		
}

uchar DS18B20_RD_CHAR()	//先读低位
{
	uchar num;
	uchar num1;
	uchar byte=0;
	for(num1=0;num1<8;num1++)
	{
		DQ=0;  	//拉低
		_nop_();
		DQ=1;
		for(num=0;num<1;num++);  // <10us 	
		byte>>=1;
		if(DQ==1)
			byte|=0x80;
		else 
			byte|=0x00;
		DQ=1;	//拉高
		_nop_();
		_nop_();
		for(num=0;num<20;num++);  //  >60us
		
	}
	return byte;
}

void DS18B20_WENDU()
{
	uchar temperaturel=0;
	uchar temperatureh=0;
	if(init_DS18B20()==0)
	{
		DS18B20_WR_CHAR(0xcc);
		DS18B20_WR_CHAR(0x44);
		delay1ms(1000);
		if(init_DS18B20()==0)
		{	
			DS18B20_WR_CHAR(0xcc);
			DS18B20_WR_CHAR(0xBE);
			_nop_();
			temperaturel=DS18B20_RD_CHAR();
			temperatureh=DS18B20_RD_CHAR();
			wendu=(temperatureh*256+temperaturel)*0.625; //温度比正常大10倍
			init_DS18B20();
		}			
	}
}
 ////24l01
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

void Delay(uint s)
{
	uint i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}
//******************************************************************************************
uchar 	bdata sta;   //状态标志
sbit	RX_DR	=sta^6;
sbit	TX_DS	=sta^5;
sbit	MAX_RT	=sta^4;
/******************************************************************************************
/*延时函数
/******************************************************************************************/
void inerDelay_us(uchar n)
{
	for(;n>0;n--)
		_nop_();
}
//****************************************************************************************
/*NRF24L01初始化
//***************************************************************************************/
void init_NRF24L01(void)
{
    inerDelay_us(100);
 	CE=0;    // chip enable
 	CSN=1;   // Spi  disable 
 	SCK=0;   // 
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // 写发射端地址	
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P1,RX_ADDRESS, RX_ADR_WIDTH); // 写接收端地址
	SPI_RW_Reg(WRITE_REG + EN_AA, 0x03);      //  频道1自动	ACK应答允许	
	SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x03);  //  允许接收地址只有频道1，如果需要多频道可以参考Page21  
	SPI_RW_Reg(WRITE_REG + RF_CH, 0);        //   设置信道工作为2.4GHZ，收发必须一致
	SPI_RW_Reg(WRITE_REG + RX_PW_P1, RX_PLOAD_WIDTH); //设置接收数据长度，本次设置为32字节
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   		//设置发射速率为1MHZ，发射功率为最大值0dB
}


/****************************************************************************************************
/*函数：uint SPI_RW(uint uchar)
/*功能：NRF24L01的SPI写时序
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
/*函数：uchar SPI_Read(uchar reg)
/*功能：NRF24L01的SPI时序
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
/*功能：NRF24L01读写寄存器函数
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
/*函数：uint SPI_Read_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于读数据，reg：为寄存器地址，pBuf：为待读出数据地址，uchars：读出数据的个数
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
/*函数：uint SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
/*功能: 用于写数据：为寄存器地址，pBuf：为待写入数据地址，uchars：写入数据的个数
/*********************************************************************************************************/
uchar SPI_Write_Buf(uchar reg, uchar *pBuf, uchar uchars)
{
	uchar status,uchar_ctr;
	
	CSN = 0;            //SPI使能       
	status = SPI_RW(reg);   
	for(uchar_ctr=0; uchar_ctr<uchars; uchar_ctr++) //
		SPI_RW(*pBuf++);
	CSN = 1;           //关闭SPI
	return(status);    // 
}
/****************************************************************************************************/
/*函数：void SetRX_Mode(void)
/*功能：数据接收配置 
/****************************************************************************************************/
/*void SetRX_Mode(void)
{
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	CE = 1; 
	inerDelay_us(130);
}	*/
/******************************************************************************************************/
/*函数：unsigned char nRF24L01_RxPacket(unsigned char* rx_buf)
/*功能：数据读取后放如rx_buf接收缓冲区中
/******************************************************************************************************/
uchar nRF24L01_RxPacket(uchar *rx_buf)
{	 
    uchar revale=0;
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0,RX_ADDRESS, RX_ADR_WIDTH);
	CE=0;
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x1f);   		// IRQ收发完成中断响应，16位CRC	，主接收
	CE = 1; 
	inerDelay_us(130);
	sta=SPI_Read(STATUS);	// 读取状态寄存其来判断数据接收状况
	if(RX_DR)				// 判断是否接收到数据
	{
	    CE = 0; 			//SPI使能
		SPI_Read_Buf(RD_RX_PLOAD,rx_buf,RX_PLOAD_WIDTH);// read receive payload from RX_FIFO buffer
		revale =1;			//读取数据完成标志
		
	}
	SPI_RW_Reg(WRITE_REG+STATUS,sta);   //接收到数据后RX_DR,TX_DS,MAX_PT都置高为1，通过写1来清楚中断标志
	return revale;
}
/***********************************************************************************************************
/*函数：void nRF24L01_TxPacket(unsigned char * tx_buf)
/*功能：发送 tx_buf中数据
/**********************************************************************************************************/
void nRF24L01_TxPacket(uchar *tx_buf)
{
	CE=0;			//StandBy I模式	
	SPI_Write_Buf(WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // 发射端地址
	SPI_Write_Buf(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH); 			 // 装载数据	
	SPI_RW_Reg(WRITE_REG + CONFIG, 0x1e);   		 // IRQ收发完成中断响应，16位CRC，主发送
	CE=1;		 //置高CE，激发数据发送
	inerDelay_us(20);	
}

///////
main()
{
	uchar TxBuf[20]={0};
	wendu=0;
	init_1602();
	init_NRF24L01();
	delay1ms(1000);
	while(1)
	{
		if( init_DS18B20()==0)  	
     	{   
			DS18B20_WENDU(); 
			write_com(0x80);
			write_str("1#temperature");
			write_data(':');
			write_com(0x80+0x44);
			write_data((wendu/100)%10+48);
			write_data((wendu/10)%10+48);
			write_data('.');
			write_data(wendu%10+48);
			write_data(0xdf);
			write_data('c'); 
			TxBuf[1]=wendu/256;
			TxBuf[2]=wendu%256;
			BELL=0;
			delay1ms(1);
			BELL=1;
		}  
		nRF24L01_TxPacket(TxBuf);	// Transmit Tx buffer data
		TxBuf[1] = 0x00;
		TxBuf[2] = 0x00;				
		delay1ms(1000);
		sta=SPI_Read(STATUS);
		SPI_RW_Reg(WRITE_REG+STATUS,sta); 
	}
}

