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



/* ���ڽ����жϷ������ */
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
/* ϵͳ��ʼ������ */
void system_init(void)
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xDC;		//�趨��ʱ��ֵ
	TH1 = 0xDC;		//�趨��ʱ����װֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
}

