#include <REG51.H>

void system_init(void);

void Uart_send(unsigned char dat);

void Uart_sendx(unsigned char  xdat);

void Uart_datas(unsigned char data *pd_string) ;
void delay(int ms) ;
#define FOSC 12000000L
#define F38_4KHZ (256-FOSC/2/12/37900)
unsigned char *sd="fucking irda";
sbit P11 = P1^1 ;
unsigned char IRAD_S1=0;
#define uchar unsigned char
void main(void)
{
	uchar irda,i ;
	//delay(5000) ;
	system_init() ;
	while(1)
	{					
		Uart_send(0x05);
		for(i=0;i<250;i++)
		{
			for(irda=0;irda<20;irda++) ;
		}
		irda=0;
		i=0;
	}
}



/* 串口接收中断服务程序 */
void uart_int(void) interrupt 4
{	
	uchar temp ;
	//P15 = !P15 ;
	EX1 = 0 ;	
}



/* Send a byte access serial */
void Uart_send(uchar dat) 
{
	TI = 0 ;
	SBUF = dat ;
	while(!TI) ;
	TI = 0 ;
}

void Uart_sendx(uchar  xdat) 
{
	TI = 0 ;
	SBUF = xdat ;
	while(!TI) ;
	TI = 0 ;
}

/* Send a code string access serial */
/* 系统初始化程序 */
void system_init(void)
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xDC;		//设定定时初值
	TH1 = 0xDC;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
}

