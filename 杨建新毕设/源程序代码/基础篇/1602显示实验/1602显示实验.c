#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="I LIKE  MCU ";
uchar code table1[]="QQ 240691152  ";
sbit lcden=P3^7;
sbit lcdrw=P3^6;
sbit lcdrs=P3^4;
uchar num;
void delay(uint z)
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
void init() //��ʼ����
{
	lcdrw=0;
	lcden=0; //E�ĳ�ʼֵΪ�͵�ƽ������ĳ�����ߵ�ƽ�Ӷ�����EΪ������
	write_com(0x38); //д����ʾģʽָ��
	write_com(0x0e); //��ʾ�Ƿ���Լ�
	//��������
	write_com(0x06); //��ַָ��ļӼ��������Ƿ��ƶ�
	write_com(0x01); //����ָ��
	write_com(0x80+0x10); //��ʾ�ַ��ĳ�ʼλ��
}
void main()
{
	init();
	for(num=0;num<11;num++)
	{
		write_data(table[num]);
		delay(20);
	}
//	//write_com(1); //����ָ��
	write_com(0x80+0x53);  //��ʼ��ַΪ53�����ַ������˵ڶ���
	for(num=0;num<13;num++)
	{
		write_data(table1[num]);
		delay(20);
	}
	for(num=0;num<16;num++)  //�����ƶ�16��
	{
		write_com(0x18); //�����ƶ�����Ҫָ�
		delay(20);
	}
	while(1);
}

