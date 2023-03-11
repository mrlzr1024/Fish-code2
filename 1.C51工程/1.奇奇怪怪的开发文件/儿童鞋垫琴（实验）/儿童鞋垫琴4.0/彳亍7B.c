#include <reg52.h>
#include <INTRINS.H>
#include "key.h"
#define uchar unsigned char 
#define l1  262
#define l2  286
#define l3  311
#define l4  349
#define l5  392
#define l6  440
#define l7  494
#define m1  523
#define	m2  587
#define m3  659
#define	m4	 698
#define	m5	 784
#define m6	 880
#define	m7	 987
#define h1	 1046
#define h2	 1174
#define	h3	 1318
#define	h4	 1396
#define h5	 1567
#define	h6	 1760
#define	h7	 1975
sbit sound=P2^0;
unsigned int  C;
unsigned char a;
unsigned char b;
void delay()
{
	unsigned char i,j;
		for(i=0;i<250;i++)
		 for(j=0;j<250;j++)
		 		;
}
void time0() interrupt 1
{
	sound=!sound;
	TH0=(8192-C)/32;
	TL0=(8192-C)%32;
}
unsigned code table[]={l1,l2,l3,l4,l5,l6,l7,m1,m2,m3,m4,m5,m6,m7,h1,h2,h3,h4,h5,h6,h7,0xff};
void main()
{
	EA=1;
	ET0=1;
	TMOD=0x00;
	while(1)
	{
			a=key4x4();
		while(a!=21)
		{
			C=460830/table[a];
			TH0=(8192-C)/32;
			TL0=(8192-C)%32;
			TR0=1;
				for(b=0;b<2;b++)
				delay();
				TR0=0;
				sound=1;
				a=21;
		}
	}
}




