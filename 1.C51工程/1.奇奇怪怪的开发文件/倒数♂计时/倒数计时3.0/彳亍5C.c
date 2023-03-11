#include <reg51.h>
#define uchar unsigned char 
sbit P2_0=P2^3;
sbit P2_1=P2^2;
sbit A=P2^1;
sbit C=P2^0;
uchar t;
char num;
char num1;
char num2;
char num3;
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=200;k>0;k--);
}
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
uchar code table1[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void main()
{
	t=0;	//初始化
	num=9;
	num1=5;
	num2=9;
	num3=5;
	EA=1;					//标准化操作
	ET0=1;					//定时器中断允许
	TMOD=0x01;				//设定定时器模式
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=1;					 //打开定时器
	P0=~table1[num1];//
		P2_1=0;
		delay(100);
		P2_1=1;
	while(1)
 {
	if(t==20)
	{
		num--;
		P0=~table[num];
		P2_0 = 0;
		delay(5);
		P2_0 = 1;
		delay(2);
	   P0=~table1[num1];
		P2_1=0;
		delay(5);
		P2_1=1;
		t=0;
		P0=~table1[num2];
		A=0;
		delay(5);
		A=1;
		P0=~table1[num3];
		C=0;
		delay(5);
		C=1;
	}
	else if(t!=20)
	{
		P0=~table[num];
		P2_0=0;
		delay(5);
		P2_0=1;
		 P0=~table1[num1];
		P2_1=0;
		delay(5);
		P2_1=1;
		P0=~table1[num2];
		A=0;
		delay(5);
		A=1;
		P0=~table1[num3];
		C=0;
		delay(5);
		C=1;
	}
	if(num<0)
	{
		num=9;
		num1--;
	}
  if(num1<0)
	{
		num1=5;
		num2--;
	}
	else if(num2<0)
	{
		num2=9;
		num3--;
	}
		else if(num3<0)
	{
		num3=5;
	}


 }

}
void  time0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t++;	
}