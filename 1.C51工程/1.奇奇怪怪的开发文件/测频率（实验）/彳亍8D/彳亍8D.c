#include<reg51.h>
#define uchar unsigned char
sbit S=P2^0;
sbit P1_0=P1^0;
sbit H=P2^1;
sbit TEN=P2^2;
sbit O=P2^3;
int C;
int T;
char E;
int TT;
char tem; 
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
	}    	
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void main()
{
	EA=1;
	IT0=1;
	EX0=1;
	ET0=1;
	C=0;
	T=0;
	tem=1;
	TMOD=0X0a;
	TH0=(65536-921)/256;
	TL0=(65536-921)%256;
	TR0=1;	
	while(1)
	{
		E=C%10;
		P0=table[E]; //个位
		O=0;
		delay(2);
		O=1;
		delay(1);
		E=(C%100)/10;
		P0=table[E]; //十位
		TEN=0;
		delay(2);
		TEN=1;
		delay(1);
		E=(C%1000)/100;
		P0=table[E]; //百位
		H=0;
		delay(2);
		H=1;
		delay(1);
		E=C/1000;
		P0=table[E];///千位
		S=0;
		delay(2);
		S=1;
		delay(1);
	}	
}
void Time0() interrupt 1 using 0
{
		TH0=(65536-921)/256;
	    TL0=(65536-921)%256;
	 
}
void int0() interrupt 0 using 0
{
	C++;
	if(C>9999)
	{
		C=0;
	}
}