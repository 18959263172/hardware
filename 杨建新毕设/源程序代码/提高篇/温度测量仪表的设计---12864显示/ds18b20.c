///无线模块板
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit DQ=P2^0;			 //ds18b20
// 1602
sbit lcden=P3^7;
sbit lcdrs=P3^4;
sbit lcdrw=P3^6;
sbit BELL=P1^6;
uint wendu=0;
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
 while(*str!='\0')  //未结束   
 {  
  write_date(*str++);  
  delay1ms(5);  
 }  
} 

void write_pos(uchar x,uchar y)  //从第X行的第Y位置开始显示   
{  
 uchar pos;  
 if(x==1)        //第一行   
 { x=0x80;}  
 else if(x==2)  //第二行   
 { x=0x90;}  
 else if(x==3)  //第三行   
 { x=0x88;}  
 else if(x==4)  //第四行   
 { x=0x98;}  
 pos=x+y-1;     //首地址为0X80   
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
	write_str("  温度测量实验");
	write_pos(3,1);
	write_str("当前温度:");
	write_pos(3,8);
	write_str("度");
	write_pos(4,1);
	write_str("顺通电子工作室");



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

uint DS18B20_WENDU()
{
	uchar temperaturel=0,temperatureh=0;
	uint temperature=0;
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
			temperature=(temperatureh*256+temperaturel)*0.625;
			init_DS18B20();
		}
		return temperature;				
	}
}

///////
main()
{
	init_12864();
	delay1ms(1000);
	while(1)
	{
		if( init_DS18B20()==0)  	
     	{   
			wendu=DS18B20_WENDU();  
			write_pos(3,6);
			write_date((wendu/100)%10+48);
			write_date((wendu/10)%10+48);
			write_date('.');
			write_date(wendu%10+48);
			BELL=0;
			delay1ms(1);
			BELL=1;
			delay1ms(2000);
		}  
	}
}