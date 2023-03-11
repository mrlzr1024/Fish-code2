#include<reg52.h>
#include"spi.h"
#include"CharCode.h"
unsigned char a;
int tmp=0,j=0,i=0;
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

int BluetoothGet(void){
	j=0;
	init();//初始化串口
	while(j==0)
		;
	switch (a){
		case 1:
			return 0;
		case 2:
			return 1;
		case 3:
			return 2;
		case 4:
			return 3;
		case 5:
			return 4;
		case 6:
			return 5;
		case 7:
			return 6;
		case 8:
				return 7;
		default:
			break;
	}
}
void main(void){
	j=0;
	init();
	LCD_init();
	LCD_set_XY(3,9);LCD_write_char(l0);
	while(1){
	if(j==1){display(BluetoothGet()*8,5,l0);}
	}
}
void Uart() interrupt 4
{
    a = SBUF;
    RI=0; // 接收中断标志位置0；
    SBUF = a;
    while(!TI);
    TI = 0;       // 发送中断标志位置0；
	if(i==0){i++;j=0;}
	else if (i>=1){i=0;j=1;}
}
