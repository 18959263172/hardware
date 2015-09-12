//同时用两个定时器控制蜂鸣器发声，定时器0控制频率，定时器1控制同个频率持续的时间，间隔3s依次输出1，10，50,100，200,400,800,
//1k（hz）的方波。

#include <reg52.h>
#define uchar unsigned char
#define  uint unsigned  int
uint num;
uchar tt,tt1;
sbit   beep=P1^6;
void  init()
{
	num=50000;
	tt=0;
	tt1=0;
	TH0=(65536-num)/256;
	TL0=(65536-num)%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;	   
	beep=0;
	TMOD=0x11;
	EA=1;
	ET0=1;
	TR0=1;
	ET1=1;
	TR1=1;
}
void main()
{
	init();
	while(1)
	{
		
	}
}
void  timer0()  interrupt   1
{
	TH0=(65536-num)/256;
	TL0=(65536-num)%256;
	tt++;
	if(tt1<60)
	{
		if(tt==20)
		{
			tt=0;
			num=50000;
			beep=~beep;	
		}
	}
	if(60<=tt1<120)
	{
		if(tt==2)
		{
			tt=0;
			num=50000;
			beep=~beep;	
		}
	}
	if(12<=tt1<18)
	{
		if(tt==2)
		{
			tt=0;
			num=10000;
			beep=~beep;	
		}
	}
	if(180<=tt1<240)
	{
		if(tt==2)
		{
			tt=0;
			num=5000;
			beep=~beep;	
		}
	}
	if(24<=tt1<30)
	{
		if(tt==2)
		{
			tt=0;
			num=2500;
			beep=~beep;	
		}
	}
	if(300<=tt1<360)
	{
		if(tt==2)
		{
			tt=0;
			num=1250;
			beep=~beep;	
		}
	}
	if(360<=tt1<420)
	{
		if(tt==2)
		{
			tt=0;
			num=625;
			beep=~beep;	
		}
	}
	if(tt1>=420)
	{
		if(tt==2)
		{
			tt=0;
			num=500;
			beep=~beep;	
		}
	}
}
void  timer1() interrupt   3
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	tt1++;
	if(tt1==480)
	{
		tt1=0;
	}
}
