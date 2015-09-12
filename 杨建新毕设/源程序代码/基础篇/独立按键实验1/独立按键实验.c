//按住K1按键  蜂鸣器响
#include<reg52.h>
#define uint unsigned int
sbit key1=P2^4;

sbit BELL=P1^6;  //蜂鸣器

void delay(uint z)  //延迟函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	BELL=1;//关闭蜂鸣器

	while(1)
	{
		if(key1==0) 
		{
		 	delay(5);   //松手检测
			if(key1==0)
			{ BELL=0; delay(50);  BELL=1; delay(50);}  //键一按下，蜂鸣器响
		}
		
	}
}
