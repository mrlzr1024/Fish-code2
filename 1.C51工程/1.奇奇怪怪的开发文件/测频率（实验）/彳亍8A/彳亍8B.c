#include<reg51.h>
#define uchar unsigned char
uchar co;
void main()
{
	char co;
	char i;
	co=0;
	while(1)
	{

				EA=1;
				EX0=1;
				IT0=1;
				i=co;
				if(i>8)
				{
					co=0;
				}
				}
}
void int0() interrupt 0 using 0
{														
	co++;
	P1=co;
}
