#include<reg52.h>
sbit P2_0=P2^0;
sbit P3_2=P3^2;
sbit P3_3=P3^3;
void delay(void)   //delay 0.5s
{
    unsigned char a,b,c;
    for(c=98;c>0;c--)
        for(b=127;b>0;b--)
            for(a=17;a>0;a--);
}
void main(void){
	EA=1;
	EX0=1;
	EX1=1;
	IT0=1;
	IT1=1;
	P1=0XFE;
	delay();//1
	P1=0XFD;
	delay();//2
	P1=0XFB;
	delay();//3
	P1=0XF7;
	delay();//4
	P1=0XEF;
	delay();//5
	P1=0XDF;
	delay();//6
	P1=0XBF;
	delay();//7
	P1=0X7F;
	delay();
}
void inter1() interrupt 2{
	P1=0xff;
	delay();
			;
}
void inter() interrupt 0{
	delay();
	while(1){
			if(P3_2==1){
				break;
			}
			}
	}
