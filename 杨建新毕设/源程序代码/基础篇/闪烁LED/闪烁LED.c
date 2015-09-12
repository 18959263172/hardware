//∫Ï…´LED…¡À∏
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit d0=P1^7;
void delay(uchar dly)
	{
		uchar i,j;
		for(i=255;i>0;i--)
		 for(j=dly;j>0;j--);
	}

void main()
{	
	
	while(1)
 	{
	    d0=1;
        delay(255);
	    d0=0;
	    delay(255);

        }
}