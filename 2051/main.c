#include"stc.h"
#include<intrins.h>

#define FOSC 10000000L

#define T1MS (65536-FOSC/1000)      //1T模式
void Init_system();

unsigned char dig[]={0x04,0x2F,0x48,0x0a,0x23,0x12,0x10,0x0f,0x00,0x02};
unsigned char count=1000;
unsigned char time_out_flag=0;
sbit P33=P3^3;
sbit P17=P1^7;
int x=0;

void exint0() interrupt 0           //(location at 0003H)
{
    x++;
}

void tm0_isr() interrupt 1 using 1
{
    TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;                //reload timer0 high byte
    if (count-- == 0)               //1ms * 1000 -> 1s
    {
        count = 700;               //reset counter
		time_out_flag=1;
    }	
}
void main()
{
	unsigned char c,j;	
	Init_system();
	while(1)
	{
		if(time_out_flag)
		{
			time_out_flag=0;
			if(x>=0) P1=dig[0];
			if(x>20) P1=dig[1];
			if(x>40) P1=dig[2];
			if(x>80) P1=dig[3];
			if(x>100) P1=dig[4];
			if(x>120) P1=dig[5];
			if(x>140) P1=dig[6];
			if(x>180) P1=dig[7];
			if(x>180) P1=dig[8];
			if(x>280)
			{	
				P17=1;
				P33=0;
			}
			;
			x=0;
		}
		
	}
}

void Init_system()
{    
	IT0 = 1;                        //set INT0 int type (1:Falling 0:Low level)
    EX0 = 1;                    //使能INT0中断
    TMOD = 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;
}
