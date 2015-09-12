//   湿度20-90   温度0-50		采样间隔1S				无线模块板
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
	write_str("  温湿度测量实验�");
	write_pos(2,1);
	write_str("环境湿度:");
	write_pos(2,7);
	write_str("%");
	write_pos(3,1);
	write_str("当前温度:");
	write_pos(3,7);
    write_str("度");
	write_pos(4,1);
	write_str("  顺通电子工作室�");

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
		wendu=DTH11_RD_CHAR()-2;   //比正常值高2度左右
		DTH11_RD_CHAR();
		shidu=DTH11_RD_CHAR();
		DTH11_RD_CHAR();
		DTH11_RD_CHAR();
		for(num=0;num<17;num++);  //最后BIT输出后拉低总线59us
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
