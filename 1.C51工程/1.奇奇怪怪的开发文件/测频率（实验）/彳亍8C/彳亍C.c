#include<reg51.h>
sbit P3_2=P3^2;
char C;
char T;
void main()
{
	EA=1;
	IT0=1;
	EX0=1;
	ET0=1;
	C=0;
	T=0;
	TMOD=0X00;
	TH0=(65536-921)/256;
	TL0=(65536-921)%256;
	TR0=1;	
	while(1)
	;	
}
void Time0() interrupt 1 using 0
{
	P1=C;
	if(T<1000)
	{
		T++;	
	}
	else if(T>=1000)
	{
		T=0;
		TH0=(65536-921)/256;
	    TL0=(65536-921)%256;

	}
}
void int0() interrupt 0 using 0
{
	C++;
	P1=C;
}