//利用定时/计数器T1产生定时时钟,每隔10秒，发生一次声光报警
#include<reg52.h>
#define uchar unsigned char
uchar  temp,aa;
sbit  beep=P1^6;
sbit D1=P1^7;
void init()
{
 	aa=0;
	TMOD=0x10;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	EA=1;
	ET1=1;
	TR1=1;
} 
void   main	()
{
	init();
	while(1)
	{
	
	     if(aa==10)
	    	{
		    D1=0;
			beep=0;		
			}
	}
}
void   timer1()  interrupt   3
{
 	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	aa++;
    D1=1;	
	beep=1;	
}
