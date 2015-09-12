
#include<reg52.h>
#define uchar unsigned char
uchar  flag,temp;
void  init()
{
	TMOD=0x20;
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;
}
void  main()
{
	init();
	while(1)
	{
		if(flag==1)
		{ 	
			ES=0;
			flag=0;
			SBUF=temp;
			while(!TI);
			TI=0;
			ES=1;
		}
	}
}
void  ser() interrupt   4
{
	RI=0;
	temp=SBUF;
	P0=temp;
	flag=1;
}  
