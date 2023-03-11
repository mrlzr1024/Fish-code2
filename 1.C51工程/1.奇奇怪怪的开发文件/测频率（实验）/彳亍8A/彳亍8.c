#include<reg51.h>
#define uchar unsigned  char
sbit P2_0=P2^0;
sbit P2_1=P2^1;
sbit P1_0=P1^0;
char i;
void init()
{
	i=0;
	P2_0=0;
	P2_1=0;	
}
uchar code table[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00};
void time0()
{
	TMOD=0X00;
	TR0=1;
	EA=1;
	ET0=1;
}
void main()
{
	init();
	while(1)
	{
	while(P2_1==1)
		{
			if(P2_0==1)
			{
				time0();
					while(TF0==0)
					{
						;
						TF0=0;
						TH0=(65536-921)/256;
						TL0=(65536-921)%256;
						i++;
					}
					P1_0=0;	
			}
		}
	}	
}