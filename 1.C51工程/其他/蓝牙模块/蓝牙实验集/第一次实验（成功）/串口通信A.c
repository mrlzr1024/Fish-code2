#include<reg52.h>
#include"spi.h"
#include"CharCode.h"
unsigned char a[3];
int i=0,j=0;
 unsigned char rev;
/*void Delay10ms(unsigned int c){
   unsigned char a, b;
    for (;c>0;c--)
    {
        for (b=38;b>0;b--)
        {
            for (a=130;a>0;a--);
        }          
    }       
}*/
void init(void){
	EA=0;
	TMOD=0X20;
	SCON=0X50;
	TH1=0XFD;
	TL1=TH1;
	PCON=0X00;
	EA=1;
	ES=1;
	TR1=1;
	REN=1;
}
void main(void){
	init();
	LCD_init();
	LCD_set_XY(3,9);LCD_write_char(l0);
	while(1){
	if(a[0]==0x10){LCD_set_XY(20,9);LCD_write_char(l0);}
	if(a[1]==0x11){LCD_set_XY(30,9);LCD_write_char(l0);}

	}
}

void Uart() interrupt 4
{
    a[i] = SBUF;
    RI=0; // 接收中断标志位置0；
    SBUF = a[i];
    while(!TI);
    TI = 0;       // 发送中断标志位置0；
	if(i>=0&&i<=1){i++;}
	else if (i>=2){i=0;j=1;}
}
