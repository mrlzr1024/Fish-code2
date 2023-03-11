#include<reg51.h>
sbit RS=P2^7;
sbit RW=P2^6;
sbit EN=P2^5;
void delay(void)   //?? -0.000000000001us
{
    unsigned char a,b;
    for(b=15;b>0;b--)
        for(a=152;a>0;a--);
}
void init(){
	RS=0;
	WR=1;
	EN=1;
}

void main(void){
	
}
