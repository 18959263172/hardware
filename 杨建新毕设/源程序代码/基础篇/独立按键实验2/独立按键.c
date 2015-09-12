/*本程序使用4个独立按键，带有延时函数，按键一或三按下蜂鸣器响灯灭，按键二或四按下蜂鸣器灭灯亮，*/
#include<reg52.h>
#define uint unsigned int
sbit key1=P2^4;
sbit key2=P2^5;
sbit key3=P2^6;
sbit key4=P2^7;
sbit BELL=P1^6;  //蜂鸣器
sbit D=P1^7;  //LED灯
void delay(uint z)  //延迟函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void main()
{
	BELL=1;//关闭蜂鸣器
	D=1;  //关闭小灯
	while(1)
	{
		if(key1==0) 
		{
		 	delay(5);   //松手检测
			if(key1==0)
			{ BELL=0; delay(50);  BELL=1; delay(50);}  //键一按下，蜂鸣器响
		}
		if(key2==0) 
		{
		 	delay(5);   //松手检测
			if(key2==0)
			{ BELL=1; D=0; delay(50);  D=1; delay(50); }  //键二按下，蜂鸣器灭
		}
		if(key3==0) 
		{
		 	delay(5);   //松手检测
			if(key3==0)
			{ BELL=0; delay(50);  BELL=1; delay(50);}  //键三按下，蜂鸣器响
		}
		if(key4==0) 
		{
		 	delay(5);   //松手检测
			if(key4==0)
			{ BELL=1; D=0; delay(50);  D=1; delay(50);}  //键四按下，蜂鸣器灭
		}
	}
}
