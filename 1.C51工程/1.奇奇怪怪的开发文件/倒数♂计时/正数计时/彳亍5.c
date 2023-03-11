#include<reg51.h>
#define uchar unsigned char 
sbit P2_0=P2^0;
sbit P2_1=P2^1;
uchar t;
uchar num;
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=200;k>0;k--);
}
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void  time0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t++;	
}
void main()
{
	t=0;
	num=0;
	EA=1;
	ET0=1;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=1;
	while(1)
 {
	if(t==20)
	{
		num++;
		P0=table[num];
		P2_0 = 0;
		delay(50);
		P2_0 = 1;
		t=0;

	}
	else if(t!=20)
	{
		P0=table[num];
		P2_0=0;
		delay(100);
		P2_0=1;
	}
	if(num>9)
	{
		num=0;
	}
 }

}