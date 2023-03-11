#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
sbit tr=P1^0;//
sbit x=P1^3;
sbit ec=P3^2;//
sbit S=P2^0;
sbit H=P2^1;
sbit TEN=P2^2;
sbit O=P2^3;
int A;
int C;
int E;
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}    	
void init(void)
{
	tr=0;
	ec=0;
	x=0;	
}
void main(void)
{
	init();
	EA=1;
	ET0=1;
	TMOD=0x09;
	TR0=1;
	C=0;
	TH0=0;
	TL0=0;
	while(1)
	{
		x=ec;
		tr=1;
      _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	   tr=0;
	   delay(5);
	        C=A*17;
			E=C;
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
			A=0;
	}		
}
void Time0() interrupt 1 using 1
{
	TH0=(65536-9)/256;
	TL0=(65536-9)%256;
	A++;	
} 