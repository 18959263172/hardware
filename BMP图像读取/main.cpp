#include<stdio.h>
typedef struct CDBMP {
char    bfType[2] ;
char	bfSize[4] ; 
char	bfReserved1[2]  ; 
char    bfReserved2[2]; 
char    bfOffBits[4]; 
} BP;
int main()
{
	unsigned char x;
	FILE *fp;
	if(!(fp=fopen("C:\\1.bmp","r")))
	{
		printf("File open error!");
		return 0;
	}
	else 
	for(int i=0;i<50;i++)
	{
		x=fgetc(fp);
		printf("%x\n",x);
	}
	fclose(fp);
	
}