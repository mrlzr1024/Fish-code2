#include<reg51.h>
sbit Ao=P1^0;
long i;
void init()
{
	Ao=0;
}
void delay1(void)   //ÑÓÊ±1.5ms
{
    unsigned char a,b;
    for(b=197;b>0;b--)
        for(a=2;a>0;a--);
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
			delay1();
			Ao=0;
			delay20();
				
		}
}	

