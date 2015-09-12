//利用导体接触P32 蜂鸣器响
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit  beep=P1^6;
void delay(uchar dly)
{
	uchar i,j;
	for(i=255;i>0;i--)
		for(j=dly;j>0;j--) ;
}
void main()
{	
        EA=1;
		EX0=1;
		IT0=0;
	   
		while(1)
		{
		
	
		}  
}
void   exter0()  interrupt    0
{
	beep=0;
    delay(100);
 	beep=1;	
}
