#include<reg52.h>
#define uchar unsigned char   
#define uint unsigned int 
sbit RS=P3^4;                                        
sbit RW=P3^6;
sbit E=P3^7;

uchar data num[6];
uchar sec,tt,min,hour,n;
uchar data tab[]={"  :  :  "};
uchar code tab1[]={"★2011年08月19日"};
uchar code tab2[]={"★时间："};

void delay_50us(uint t)
{
 uint j;
 for(;t>0;t--);
 for(j=19;j>0;j--);
}
void delay_50ms(uint t)
{
 uint j;
 for(;t>0;t--);
 for(j=6245;j>0;j--);
}
void check_busy()
{
 uchar n;
 RW=1;
 RS=0;
 do
 {
   P1=0x00;
   E=1;
   n=P1&0x80;
   E=0;	
 }	 while(n!=0x00);
}
void write_cmd(uchar cmd)    
{
 check_busy();
 RS=0;
 RW=0;
 delay_50us(1);
 P0=cmd;
 E=1;
 delay_50us(10);
 E=0;
 delay_50us(2);
} 
void write_dat(uchar dat)  
{
 check_busy();
 RS=1;
 RW=0;
 delay_50us(1);
 P0=dat;
 E=1;
 delay_50us(10);
 E=0;
 delay_50us(2);	
}
void  init()
{

	sec=44; min=32; hour=12;
	tt=0;
	TMOD=0x01; TH0=0x4C; TL0=0x00;
	EA=1; ET0=1; TR0=1;
}
void init_12864()
{
 E=0;
 delay_50ms(2);
 write_cmd(0x30);
 delay_50us(4);
 write_cmd(0x30);
 delay_50us(4);
 write_cmd(0x0c);
 delay_50us(4);
 write_cmd(0x01);
 delay_50us(240);  
 write_cmd(0x06);
 delay_50us(10);
}
void show_HZ(uchar adr,const uchar * pt,uchar num)
{
    uchar i;	
    write_cmd(adr); 
   	for(i = 0;i < (num*2);i++) 
        write_dat(*(pt++)); 
}
void diaplay()
{
	uchar i;
	write_cmd(0x94);
	for(i=0;i<9;i++)
	{ write_dat(tab[i]); }
}


void main()
{
	init();
	init_12864();
	show_HZ(0x80,tab1,8);
	show_HZ(0x90,tab2,4);
	while(1)
	{
		if(tt==20)
		{
			tt=0;
			sec++;
			if(sec==60)
			{
				sec=0;
				min++;
				if(min==60)
				{
					min=0;
					hour++;
					if(hour==24)
					{
						hour=0;
					}	   
				}	
			}
		}
		tab[0]=hour/10+0x30;
		tab[1]=hour%10+0x30;
		tab[3]=min/10+0x30;
		tab[4]=min%10+0x30;
		tab[6]=sec/10+0x30;
		tab[7]=sec%10+0x30;
		diaplay();
	}
}
void  timer0()  interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tt++;
}

