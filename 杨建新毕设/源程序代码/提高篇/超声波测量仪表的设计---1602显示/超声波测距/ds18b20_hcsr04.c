///无线模块板
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
// hc-sr04  超声波
sbit TRIG=P2^1;
sbit ECHO=P2^2;
//ds18b20  温度传感器
sbit DQ=P2^0;			 
// 1602  液晶
sbit lcdrs=P3^4;
sbit lcdrw=P3^6;
sbit lcden=P3^7;
sbit BELL=P1^6;
uint wendu=0;
uint t1;
bit cuowu;
////////  1602
void delay1ms(uint z)   //延迟函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=114;y>0;y--);
}

void write_com(uchar com)   
{
	lcdrs=0;
	P0=com;
	delay1ms(5);
	lcden=1;
	delay1ms(5);
	lcden=0;
}

void write_data(uchar date)
{
	lcdrs=1;
	P0=date;
	delay1ms(5);
	lcden=1;
	delay1ms(5);
	lcden=0;
}
void write_str(uchar *str)  
{  
 while(*str!='\0')  //未结束   
 {  
  write_data(*str++);  
  delay1ms(1);  
 }  
} 
void init_1602()
{
//	uchar num;
//	uchar table[16]={0};
//	uchar table1[16]={0}; 
	lcdrw=0;
	lcden=0;
	write_com(0x38);	
	write_com(0x0e);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
/*	for(num=0;num<16;num++)
	{
		write_data(table[num]);
		delay1ms(10);
	}
	write_com(0x80+0x40);
	for(num=0;num<16;num++)
	{
		write_data(table1[num]);
		delay1ms(10);
	}
 */
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

void DS18B20_WENDU()
{
	uchar temperaturel=0;
	uchar temperatureh=0;
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
			wendu=(temperatureh*256+temperaturel)*0.625; //温度比正常大10倍
			init_DS18B20();
		}			
	}
}

///////
main()
{
	unsigned long sj;
	uint s;
	TRIG=0;
	EA=1;
	ET1=1;
	ET0=1;
	TMOD=0x01;
	TH0=0;
	TL0=0;
	s=0;
	TR0=0;
	wendu=0;
	init_1602();
	delay1ms(1000);
	while(1)
	{
		if( init_DS18B20()==0)  	
     	{   
			DS18B20_WENDU();  
			write_com(0x80);
			write_str("   Tem:");
			write_data((wendu/100)%10+48);
			write_data((wendu/10)%10+48);
			write_data('.');
			write_data(wendu%10+48);
			write_data(0xdf);
			write_data('C');
			BELL=0;
			delay1ms(1);
			BELL=1;
		}  
		TRIG=1;
	 	_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		TRIG=0;
		while(!ECHO);
		TR0=1;
		while(ECHO);
		TR0=0;
	
		sj=TH0*256+TL0;
		s=sj*(331.45+61*wendu/10/100)/200/10; 	
		 			   
		if((s>6000)||(cuowu==1))
		{ 	
			write_com(0x80+0x40);
			write_str("Distance");
			write_data(':');
			write_data('-');
			write_data('.');
			write_data('-');
			write_data('-');
			write_data('-');
		}
		else
		{ 
			write_com(0x80+0x40);
			write_str("Distance");
			write_data(':');
			write_data(s/1000%10+48);
			write_data('.');
		   	write_data(s/100%10+48);
		   	write_data(s/10%10+48);
			write_data(s%10+48);
			write_data('m');
		}
		TH0=0;
	    TL0=0;	
		delay1ms(2000);


	}
}

void time0() interrupt 1
{  
    cuowu=1;  

}
