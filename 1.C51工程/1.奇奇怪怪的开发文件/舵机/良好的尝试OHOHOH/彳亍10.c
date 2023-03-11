#include<reg51.h>
sbit Ao=P1^0;
char i;
long s;
void init()
{
	Ao=0;
}
void InitTimer0(void)//ÑÓÊ±0.1ms
{
    TMOD = 0x01;
    TH0 = 0x0FF;
    TL0 = 0x0A4;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void delay20(void)   //ÑÓÊ±20ms
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=222;b>0;b--)
            for(a=40;a>0;a--);
}

void main(void)
{
	init();
	while(1)
		{
			Ao=1;
			InitTimer0();
			if(i>=2)
			{
				Ao=0;
				i=0;
				TR0=0;
			}
			delay20();
		}
}
void time0() interrupt 1 using	1
{
		i++;
	    TH0 = 0x0FF;
    	TL0 = 0x0A4;
}

