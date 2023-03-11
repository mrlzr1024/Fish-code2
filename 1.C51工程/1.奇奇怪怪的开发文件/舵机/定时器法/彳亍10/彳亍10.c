#include<reg51.h>
sbit Ao=P1^1 ;
void init()
{
	Ao=0;
}
void InitTimer0(void)
{					 //0.5ms
    TMOD = 0x01;
  TH0 = 0x0F8;
    TL0 = 0x30;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void delay(void)   //Îó²î -0.000000000005us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=222;b>0;b--)
            for(a=40;a>0;a--);
}


void main(void)
{
	TMOD=0x01;
    EA = 1;
    ET0 = 1;
	init();
	while(1)
		{
				Ao=1;
					InitTimer0();
					delay();

		}
}	

 void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x0F8;
    TL0 = 0x0CD;
    init();
	TR0=0;
}
