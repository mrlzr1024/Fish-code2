#include <reg51.h>
#include <INTRINS.H>
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
sbit sound=P3^6;
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
unsigned code table[]={//前奏
l6, l5, l4, l3,
m6,m7,h1,h2,h3, m6,m6, m6,h3, m6, h3,
m6,m7,h1,h2,h3, m6, m6,h3, m6, h3,
m6,m7,h1,h3,h2,m6,m6, h2,
m6,m7,h1,h2,h3, m6, m6,h2, m6,h1,h2,h3,h5,
m6,m7,h1,h2,h3, m6,m6, m6,h3, m6, h3,
m6,m7,h1,h3,h2, m6, m6,h2, m6, h1,h2,h3,h6,
//主旋律
m6,m7,h1,h2,h3, m6,h3,h2,m6,
m6,m7,h1, m7,m6,m5, m3,m5,m6,
m6,m6,m6,m7,h1,h2,h3, m6, m6,h2,h1,m5,
m5,m6, m7,m6,m7, h1,m7,h1, h2,h1,h2, h5,
//间奏
l6,l7,m1,m2,m3, l6,l6, l6,m3, l6, m3,
l6,l7,m1,m2,m3, l6,l6,m2, l6, m2,
l6,l7,m1,m3,m2, l6, l6, m2,
l6,l7,m1,m2,m3, l6, l6,m2, l6,m1,m2,m3,m5,
l6,l7,m1,m2,m3, l6,l6, l6,m3, l6, m3,
l6,l7,m1,m3,m2,l6, l6,m2, l6, m1,m2,m3,m6,
//主旋律接.上
l6,l7,m1,m2,m3, l6,m3,m2,l6, l6,l7, m1, l7,l6,l5,l3,l5,l6,
l6,l6,l6,l7,m1,m2,m3,l6,l6,m2,m1,l5,
l5,l6,l7,l6,l7, m1,l7,m1, m2,m1,m2,m5,
m6,m7,h1,h2,h3, m6,h3,h2,m6,
m6,m7,h1, m7,m6,m5, m3,m5,m6,
m6,m6,m6,m7,h1,h2,h3, m6, m6,h2,h1,m5,
m5,m6, m7,m6,m7, h1,m7,h1, h2,h1,h2, h5,
0xff};
void main()
{
	EA=1;
	ET0=1;
	TMOD=0x00;
	while(1)
	{
		a=0;
		while(a!=0xff)
		{
			C=460830/table[a];
			TH0=(8192-C)/32;
			TL0=(8192-C)%32;
			TR0=1;
				for(b=0;b<2;b++)
				delay();
					TR0=0;
					a++;
		}
	}
}




