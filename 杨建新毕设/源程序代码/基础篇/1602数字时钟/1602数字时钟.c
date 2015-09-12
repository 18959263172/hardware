//按键K1 加  按键K2  减  按键K3 选择
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="Date: 2011-11-22";
uchar code table1[]="  Time: 15:59:30";
sbit lcden=P3^7;
sbit lcdrw=P3^6;
sbit lcdrs=P3^4;
sbit key1=P2^4;  
sbit key2=P2^5;    //三个按键
sbit key3=P2^6;
uint keyflag;   //标志位
uchar num,count;
uchar sec,min,hour,day,month,year;
void delay(uint z)   //延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)   //命令子函数command 
{
	lcdrs=0;//接受指令
	P0=com; //给P0口送指令码
	delay(5);
	lcden=1; //E变为高电平
	delay(5);//在此延迟期间，将指令送入
	lcden=0; //E变为低电平，高脉冲结束
}

void write_data(uchar date)  //数据子函数data
{
	lcdrs=1; //接受数据
	P0=date; //给P0口送数据
	delay(5);
	lcden=1;  //E变为高电平
	delay(5); //在此延迟期间，将数据送入
	lcden=0; //E变为低电平，高脉冲结束
}
void write_time(uchar add,uchar date)    //写入时间函数
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+add);
	write_data(0x30+shi);
	write_data(0x30+ge);
}
void write_date(uchar add,uchar dat)   //写入日期函数
{
	uchar shi,ge;
	shi=dat/10;
	ge=dat%10;
	write_com(0x80+add);
	write_data(0x30+shi);
	write_data(0x30+ge);
}
void init() //初始函数
{
	year=11; month=11; day=22; hour=15; min=59; sec=30;
	lcdrw=0;
	lcden=0; //E的初始值为低电平，后面的程序给高电平从而满足E为高脉冲
	write_com(0x38); //写入显示模式指令
	write_com(0x0e); //显示是否打开以及光标的设置
	write_com(0x06); //地址指针的加减和整屏是否移动
	write_com(0x01); //清屏指令
	write_com(0x80+0x00); //显示字符的初始位置
	for(num=0;num<16;num++)
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(0x80+0x40);  //起始地址为53，将字符调到了第二行
	for(num=0;num<16;num++)
	{
		write_data(table1[num]);
		delay(20);
	}
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;    //开中断
	TR0=1;
}
void keyscan()   //按键函数
{
	if(key1==0)	
	{
		delay(5);
		if(key1==0)
		{	keyflag++;   //键一按下，标志位加一
			while(!key1);
			if(keyflag==1)   
			{
				TR0=0;  //关中断
				write_com(0x80+0x40+14);   //调整秒
				write_com(0x0f);   //光标闪烁
			}  
			if(keyflag==2)
			{
				write_com(0x80+0x40+11);  //调整分
			}
			if(keyflag==3)
			{
				write_com(0x80+0x40+8);  //调整时
			}
			if(keyflag==4)
			{
				write_com(0x80+14);  //调整日	
			}
			if(keyflag==5)
			{
				write_com(0x80+11);	//调整月
			}
			if(keyflag==6)
			{
				write_com(0x80+8);	//调整年
			}
			if(keyflag==7)
			{
				keyflag=0;   //标志位复位
				write_com(0x0c);   //关闭光标的闪烁
				TR0=1;   //重新开启中断，走秒
			}	
		}
	}
		if(keyflag!=0)
		{
			if(key2==0)
			{
				delay(5);   //松手检测
				if(key2==0)   //按键二对所调整的数值加一
				{
					while(!key2);
					if(keyflag==1)
					{
						sec++;
						if(sec==60)
							sec=0;
						write_time(14,sec);
						write_com(0x80+0x40+14);
					}
					if(keyflag==2)
					{
						min++;
						if(min==60)
							min=0;
						write_time(11,min);
						write_com(0x80+0x40+11);
					}
					if(keyflag==3)
					{
						hour++;
						if(hour==24)
							hour=0;
						write_time(8,hour);
						write_com(0x80+0x40+8);
					}
					if(keyflag==4)
					{
						day++;
						if(day==32)
							day=0;
						write_date(14,day);
						write_com(0x80+14);
					}
					if(keyflag==5)
					{
						month++;
						if(month==13)
							month=0;
						write_date(11,month);
						write_com(0x80+11);
					}
					if(keyflag==6)
					{
						year++;
						if(year==100)
							year=0;
						write_date(8,year);
						write_com(0x80+8);
					}
				}
			}
		}
			if(key3==0)
			{
				delay(5);
				if(key3==0)   //按键三对所调整的数值减一
				{ 
					while(!key3);
					if(keyflag==1)
					{
						sec--;
						if(sec==-1)
							sec=59;
						write_time(14,sec);
						write_com(0x80+0x40+14);
					}
					if(keyflag==2)
					{
						min--;
						if(min==-1)
							min=59;
						write_time(11,min);
						write_com(0x80+0x40+11);
					}
					if(keyflag==3)
					{
						hour--;
						if(hour==-1)
							hour=23;
						write_time(8,hour);
						write_com(0x80+0x40+8);
					}
					if(keyflag==4)
					{
						day--;
						if(day==0)
							day=31;
						write_date(14,day);
						write_com(0x80+15);
					}
					if(keyflag==5)
					{
						month--;
						if(month==0)
							month=12;
						write_date(11,month);
						write_com(0x80+11);
					}
					if(keyflag==6)
					{
						year--;
						if(year==-1)
							year=99;
						write_date(8,year);
						write_com(0x80+8);
					}
				}
			}
}
void main()
{
	init();
	while(1)
	{
		keyscan();
	}
}
void timer0() interrupt 1   //中断函数
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	if(count==18)
		{
			count=0;
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
					write_time(8,hour);
				}
				write_time(11,min);
			}
			write_time(14,sec);			
		}	
}
