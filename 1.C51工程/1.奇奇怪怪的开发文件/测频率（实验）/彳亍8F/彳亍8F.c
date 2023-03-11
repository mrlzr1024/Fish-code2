#include<reg51.h>
sbit ui=P3^2;
#define uchar unsigned char
sbit S=P2^0;
sbit P1_0=P1^0;
sbit H=P2^1;
sbit TEN=P2^2;
sbit O=P2^3;
int C;
char E;
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
	}    	
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 
void main()
{
	TMOD=0x0a;
	EA=1;
	ET0=0;
	TR0=1;
	TH0=0;
	TL0=0;
	while(1)
	{
		while(ui==0)
		  ;
		  TL0=0;
		while(ui==1)
		  ;
		  E=TL0;
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