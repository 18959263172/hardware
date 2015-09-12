#include "reg52.h"
#include "intrins.h"
sbit RS = P3^4 ;
sbit RW = P3^6 ;
sbit EN = P3^7 ;
sbit D=P2^1;
#define PORT P0
#define SET_DATA RS = 1 ;
#define SET_INC RS = 0 ;
#define SET_READ RW = 1 ;
#define SET_WRITE RW = 0 ;
#define SET_EN EN = 1 ;
#define CLR_EN EN = 0 ;
#define uchar unsigned char   
#define uint unsigned int 
void check_busy(void)  //æ��⺯��
{
unsigned int nTimeOut=0;
SET_INC
SET_READ
CLR_EN
SET_EN
while((PORT&0x80)&&(++nTimeOut!=0));
CLR_EN
SET_INC
SET_READ
}

void write_cmd(unsigned char byCmd)//��������
{
check_busy();
SET_INC
SET_WRITE
CLR_EN
PORT=byCmd;
_nop_();
_nop_();
SET_EN
_nop_();
_nop_();
CLR_EN
SET_READ
SET_INC
}
void write_dat(unsigned char byData) //��������
{
check_busy();
SET_DATA
SET_WRITE
CLR_EN
PORT=byData;
_nop_();
_nop_();
SET_EN
_nop_();
_nop_();
CLR_EN
SET_READ
SET_INC
}

void v_DelayMs_f(unsigned int nDelay)//��ʱ
{
unsigned int i;
for(;nDelay > 0;nDelay--)
{
for(i=125;i>0;i--);
}
}

void LCD_init(void)//��ʼ��
{
write_cmd(0x30);//����ָ�
v_DelayMs_f(50);
write_cmd(0x01);//����
v_DelayMs_f(50);
write_cmd(0x06);//�������
v_DelayMs_f(50);
write_cmd(0x0c);//����ʾ
}
void set_address(unsigned char x,y)//��ַת��
{
unsigned char byAddress;
switch(y)
{
case 0 :byAddress=0x80+x;
break;
case 1 :byAddress=0x90+x;
break;
case 2 :byAddress=0x88+x;
break;
case 3 :byAddress=0x98+x;
break;
default :
break;
}
write_cmd( byAddress ) ;
}
void put_string( unsigned char x, unsigned char y, unsigned char *pData )
{
set_address( x, y ) ;
while( *pData != '\0' )
{
write_dat( *pData++ ) ;
}
}

void main( void )
{
LCD_init() ;
D=0;
put_string( 0,0, "��˳ͨ���ӹ����ҡ�") ;
put_string( 1,1, "��ӭ���ٱ���") ;
put_string( 0,2, "�ססססססס�") ;
put_string( 0,3, "�����ṩ����֧��") ;

 while( 1 ) ;
}
