//��סK1����  ��������
#include<reg52.h>
#define uint unsigned int
sbit key1=P2^4;

sbit BELL=P1^6;  //������

void delay(uint z)  //�ӳٺ���
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	BELL=1;//�رշ�����

	while(1)
	{
		if(key1==0) 
		{
		 	delay(5);   //���ּ��
			if(key1==0)
			{ BELL=0; delay(50);  BELL=1; delay(50);}  //��һ���£���������
		}
		
	}
}
