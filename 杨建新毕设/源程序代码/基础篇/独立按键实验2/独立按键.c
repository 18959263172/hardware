/*������ʹ��4������������������ʱ����������һ�������·���������𣬰��������İ��·������������*/
#include<reg52.h>
#define uint unsigned int
sbit key1=P2^4;
sbit key2=P2^5;
sbit key3=P2^6;
sbit key4=P2^7;
sbit BELL=P1^6;  //������
sbit D=P1^7;  //LED��
void delay(uint z)  //�ӳٺ���
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	BELL=1;//�رշ�����
	D=1;  //�ر�С��
	while(1)
	{
		if(key1==0) 
		{
		 	delay(5);   //���ּ��
			if(key1==0)
			{ BELL=0; delay(50);  BELL=1; delay(50);}  //��һ���£���������
		}
		if(key2==0) 
		{
		 	delay(5);   //���ּ��
			if(key2==0)
			{ BELL=1; D=0; delay(50);  D=1; delay(50); }  //�������£���������
		}
		if(key3==0) 
		{
		 	delay(5);   //���ּ��
			if(key3==0)
			{ BELL=0; delay(50);  BELL=1; delay(50);}  //�������£���������
		}
		if(key4==0) 
		{
		 	delay(5);   //���ּ��
			if(key4==0)
			{ BELL=1; D=0; delay(50);  D=1; delay(50);}  //���İ��£���������
		}
	}
}
