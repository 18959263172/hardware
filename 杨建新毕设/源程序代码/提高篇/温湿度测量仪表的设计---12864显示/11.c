//   Êª¶È20-90   ÎÂ¶È0-50		²ÉÑù¼ä¸ô1S				ÎÞÏßÄ£¿é°å
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit DQ=P2^3;			 //DTH11
// 1602
sbit lcden=P3^7;
sbit lcdrs=P3^4;
sbit lcdrw=P3^6;
sbit BELL=P1^6;
uchar wendu;
uchar shidu;
////////  12864
void delay1ms(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}
void  write_com(uchar com)
{ 	
	lcdrs=0;
	P0=com;
	delay1ms(1);
	lcden=1;
	delay1ms(1);
	lcden=0;

}
void write_date(uchar date)
{
	lcdrs=1;
	P0=date;
	delay1ms(1);
	lcden=1;
	delay1ms(1);
	lcden=0;
}

void write_str(uchar *str)  
{  
 while(*str!='\0')  //Î´½áÊø   
 {  
  write_date(*str++);  
  delay1ms(5);  
 }  
} 

void write_pos(uchar x,uchar y)  //´ÓµÚXÐÐµÄµÚYÎ»ÖÃ¿ªÊ¼ÏÔÊ¾   
{  
 uchar pos;  
 if(x==1)        //µÚÒ»ÐÐ   
 { x=0x80;}  
 else if(x==2)  //µÚ¶þÐÐ   
 { x=0x90;}  
 else if(x==3)  //µÚÈýÐÐ   
 { x=0x88;}  
 else if(x==4)  //µÚËÄÐÐ   
 { x=0x98;}  
 pos=x+y-1;     //Ê×µØÖ·Îª0X80   
 write_com(pos);  
} 

void init_12864()
{	
	lcdrw=0; 
	lcden=0;
	write_com(0x01);
	delay1ms(5);
	write_com(0x30);	
	write_com(0x06);
	write_com(0x0c);
	write_com(0x88);
	write_pos(1,1);
	write_str("  ÎÂÊª¶È²âÁ¿ÊµÑéÆ");
	write_pos(2,1);
	write_str("»·¾³Êª¶È:");
	write_pos(2,7);
	write_str("%");
	write_pos(3,1);
	write_str("µ±Ç°ÎÂ¶È:");
	write_pos(3,7);
    write_str("¶È");
	write_pos(4,1);
	write_str("  Ë³Í¨µç×Ó¹¤×÷ÊÒ§");

}
/////////  DTH11

bit init_DTH11()
{
	bit flag;
	uchar num;
	DQ=0;
	delay1ms(19);	  // >18ms
	DQ=1;
	for(num=0;num<10;num++);	  // 20-40us			 34.7us

	for(num=0;num<12;num++);
	flag=DQ;
	for(num=0;num<11;num++);	//DTHÏìÓ¦80us

	for(num=0;num<24;num++);   	//DTHÀ­¸ß80us
	return flag;
}

uchar DTH11_RD_CHAR()
{
	uchar byte=0;
	uchar num;
	uchar num1;
	while(DQ==1);
	for(num1=0;num1<8;num1++)
	{
		while(DQ==0);
		byte<<=1;			  //¸ßÎ»ÔÚÇ°
		for(num=0;DQ==1;num++);
		if(num<10)
			byte|=0x00;
		else 
			byte|=0x01;
	}
	return byte;
}
void  DTH11_DUSHU()
{
	uchar num;
	if(init_DTH11()==0)
	{	
		wendu=DTH11_RD_CHAR()-2;   //±ÈÕý³£Öµ¸ß2¶È×óÓÒ
		DTH11_RD_CHAR();
		shidu=DTH11_RD_CHAR();
		DTH11_RD_CHAR();
		DTH11_RD_CHAR();
		for(num=0;num<17;num++);  //×îºóBITÊä³öºóÀ­µÍ×ÜÏß59us
		DQ=1;
		BELL=0;
		delay1ms(1);
		BELL=1;	
	}
}


/////////

main()
{
	wendu=0;
	shidu=0;
	delay1ms(1000);		  //DTH11¿ªÊ¼1sÓÐ´íÎóÊä³ö
	init_12864();
	while(1)
	{
		DTH11_DUSHU();
		write_pos(2,6);
		write_date(wendu/10%10+48);
		write_date(wendu%10+48);
		write_pos(3,6);
		write_date(shidu/10%10+48);
		write_date(shidu%10+48);
		delay1ms(2000);
	}


}
