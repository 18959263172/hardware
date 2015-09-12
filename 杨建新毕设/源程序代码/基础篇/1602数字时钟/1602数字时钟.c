//����K1 ��  ����K2  ��  ����K3 ѡ��
#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="Date: 2011-11-22";
uchar code table1[]="  Time: 15:59:30";
sbit lcden=P3^7;
sbit lcdrw=P3^6;
sbit lcdrs=P3^4;
sbit key1=P2^4;  
sbit key2=P2^5;    //��������
sbit key3=P2^6;
uint keyflag;   //��־λ
uchar num,count;
uchar sec,min,hour,day,month,year;
void delay(uint z)   //��ʱ����
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)   //�����Ӻ���command 
{
	lcdrs=0;//����ָ��
	P0=com; //��P0����ָ����
	delay(5);
	lcden=1; //E��Ϊ�ߵ�ƽ
	delay(5);//�ڴ��ӳ��ڼ䣬��ָ������
	lcden=0; //E��Ϊ�͵�ƽ�����������
}

void write_data(uchar date)  //�����Ӻ���data
{
	lcdrs=1; //��������
	P0=date; //��P0��������
	delay(5);
	lcden=1;  //E��Ϊ�ߵ�ƽ
	delay(5); //�ڴ��ӳ��ڼ䣬����������
	lcden=0; //E��Ϊ�͵�ƽ�����������
}
void write_time(uchar add,uchar date)    //д��ʱ�亯��
{
	uchar shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+add);
	write_data(0x30+shi);
	write_data(0x30+ge);
}
void write_date(uchar add,uchar dat)   //д�����ں���
{
	uchar shi,ge;
	shi=dat/10;
	ge=dat%10;
	write_com(0x80+add);
	write_data(0x30+shi);
	write_data(0x30+ge);
}
void init() //��ʼ����
{
	year=11; month=11; day=22; hour=15; min=59; sec=30;
	lcdrw=0;
	lcden=0; //E�ĳ�ʼֵΪ�͵�ƽ������ĳ�����ߵ�ƽ�Ӷ�����EΪ������
	write_com(0x38); //д����ʾģʽָ��
	write_com(0x0e); //��ʾ�Ƿ���Լ���������
	write_com(0x06); //��ַָ��ļӼ��������Ƿ��ƶ�
	write_com(0x01); //����ָ��
	write_com(0x80+0x00); //��ʾ�ַ��ĳ�ʼλ��
	for(num=0;num<16;num++)
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(0x80+0x40);  //��ʼ��ַΪ53�����ַ������˵ڶ���
	for(num=0;num<16;num++)
	{
		write_data(table1[num]);
		delay(20);
	}
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;    //���ж�
	TR0=1;
}
void keyscan()   //��������
{
	if(key1==0)	
	{
		delay(5);
		if(key1==0)
		{	keyflag++;   //��һ���£���־λ��һ
			while(!key1);
			if(keyflag==1)   
			{
				TR0=0;  //���ж�
				write_com(0x80+0x40+14);   //������
				write_com(0x0f);   //�����˸
			}  
			if(keyflag==2)
			{
				write_com(0x80+0x40+11);  //������
			}
			if(keyflag==3)
			{
				write_com(0x80+0x40+8);  //����ʱ
			}
			if(keyflag==4)
			{
				write_com(0x80+14);  //������	
			}
			if(keyflag==5)
			{
				write_com(0x80+11);	//������
			}
			if(keyflag==6)
			{
				write_com(0x80+8);	//������
			}
			if(keyflag==7)
			{
				keyflag=0;   //��־λ��λ
				write_com(0x0c);   //�رչ�����˸
				TR0=1;   //���¿����жϣ�����
			}	
		}
	}
		if(keyflag!=0)
		{
			if(key2==0)
			{
				delay(5);   //���ּ��
				if(key2==0)   //������������������ֵ��һ
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
				if(key3==0)   //������������������ֵ��һ
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
void timer0() interrupt 1   //�жϺ���
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
