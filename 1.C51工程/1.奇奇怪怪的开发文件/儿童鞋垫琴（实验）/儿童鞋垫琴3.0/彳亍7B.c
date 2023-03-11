#include<reg51.h>
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
sbit sound=P3^7;
unsigned int  C;
unsigned char a;
unsigned char b;
unsigned char d;
unsigned char e; 
unsigned char f;  
sbit k0=P2^3;
sbit k1=P1^0;
sbit k2=P1^1;
sbit k3=P1^2;
sbit k4=P1^3;
sbit k5=P1^4;
sbit k6=P1^5;
sbit k7=P1^6;
sbit k8=P2^0;
sbit k9=P2^1;
sbit k10=P2^2;
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
	d=1;
	e=1;
	f=1;
	while(1)
	{
		a=21;
					if(k1==0&k8==0)
						a=0;
					if(k2==0&k8==0)
						a=1;
					if(k3==0&k8==0)
						a=2;
					if(k4==0&k8==0)
						a=3;
					if(k5==0&k8==0)
						a=4;
					if(k6==0&k8==0)
						a=5;
					if(k7==0&k8==0)
						a=6;
					if(k1==0&k9==0)
						a=7;
					if(k2==0&k9==0)
						a=8;
					if(k3==0&k9==0)
						a=9;
					if(k4==0&k9==0)
						a=10;
					if(k5==0&k9==0)
						a=11;
					if(k6==0&k9==0)
						a=12;
					if(k7==0&k9==0)
						a=13;
					if(k1==0&k10==0)
						a=14;
					if(k2==0&k10==0)
						a=15;
					if(k3==0&k10==0)
						a=16;
					if(k4==0&k10==0)
						a=17;
					if(k5==0&k10==0)
						a=18;
					if(k6==0&k10==0)
						a=19;
					if(k7==0&k10==0)
						a=20;
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




