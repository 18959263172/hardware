//   湿度20-90   温度0-50		采样间隔1S				无线模块板
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
//sbit DQ=P3^5;
//sbit d1=P2^3;
//sbit d2=P2^4;
//sbit d3=P2^5;
sbit DQ=P2^3;			 //DTH11
// 1602
sbit lcden=P3^7;
sbit lcdrs=P3^4;
sbit lcdrw=P3^6;
sbit BELL=P1^6;
uchar wendu;
uchar shidu;
////////  1602
void delay1ms(uint z)
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
	uchar table[16]={0};
	uchar table1[16]={0}; 
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
	for(num=0;num<11;num++);	//DTH响应80us

	for(num=0;num<24;num++);   	//DTH拉高80us
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
		byte<<=1;			  //高位在前
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
		wendu=DTH11_RD_CHAR();   //比正常值高7度左右
		DTH11_RD_CHAR();
		shidu=DTH11_RD_CHAR();
		DTH11_RD_CHAR();
		DTH11_RD_CHAR();
		for(num=0;num<17;num++);  //最后BIT输出后拉低总线50us
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
	delay1ms(1000);		  //DTH11开始1s有错误输出
	init_1602();
	while(1)
	{
		DTH11_DUSHU();
		write_com(0x80);
		write_str("   Hum:");
		write_data(wendu/10%10+48);
		write_data(wendu%10+48);
		write_data('%');
		write_com(0x80+0x40);
		write_str("   Tem:");
		write_data(shidu/10%10+48);
		write_data(shidu%10+48);
	    write_data(0xdf);
		write_data('c');
		delay1ms(2000);
	}


}
