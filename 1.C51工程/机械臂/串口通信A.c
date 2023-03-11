/*
 * @Author: your name
 * @Date: 2021-11-24 14:08:41
 * @LastEditTime: 2021-12-08 12:53:26
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \机械臂\串口通信A.c
 */
#include "Uart.h"
unsigned char a;
int tmp=0,j=0,i=0;
 unsigned char rev;
void Delay10ms(unsigned int c){
   unsigned char a, b;
    for (;c>0;c--)
    {
        for (b=38;b>0;b--)
        {
            for (a=130;a>0;a--);
        }          
    }       
}
void Uart_init(void){
	EA=0;
	TMOD|=0X20;
	SCON=0X50;
	TH1=0XFD;
	TL1=TH1;
	PCON=0X00;
	EA=1;
	ES=1;
	TR1=1;
	REN=1;
	PT1=1;
	PT0=0;
	PS=1;
//	PX0=0;
}
/***************************************************
 * 函数名称：BluetoothGet
 * 入口参数：无
 * 输出：无
 * 功能：识别蓝牙
* 备注：识别两次相同的字
 * *************************************************/
int BluetoothGet(void){
//	j=0;
	Uart_init();//初始化串口
//	while(j==0)
//		;
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
			while(a!=0)
					;
			return 4;
		case 6:
			while(a!=0)
					;
			return 5;
		case 7:
			while(a!=0)
					;
			return 6;
		case 8:
			while(a!=0)
					;
			return 7;
		case 9:
			while(a!=0)
					;
			return 8;
		case  0xff:
			return 9;
		default:
			break;
	}
	return -1;
}
/***************************************************
 * 函数名称：BluetoothGetOnce
 * 入口参数：无
 * 输出：无
 * 功能：识别蓝牙
* 备注：识别一次相同的字
 * *************************************************/
int BluetoothGetOnce(void){
	int val=0;
	static unsigned char R;
	Uart_init();
	R=a;
	switch (R){
		case 0x01:
			val= 0;
			break;
		case 0x02:
			val= 1;
			break;		
		case 0x03:
			val= 2;
			break;
		case 0x04:
			val= 3;
			break;
		case 0x05:
			val= 4;
			break;
		case 0x06:
			val= 5;
			break;
		case 0x07:
			val= 6;
			break;
		case 0x08:
			val= 7;
			break;
		case 0x09:
			val= 8;
			break;
		case  0xff:
			val= 9;
			break;
		case 0x00:
			val=-1;
			break;
		default:
				val=-1;
			break;
	}
	if(val!=4&&val!=5&&val!=-1){
				while(a!=0)
					;
	}
	return val;
}

/*void main(void){
//	j=0;
//	init();
//	LCD_init();
//	LCD_set_XY(3,9);LCD_write_char(l0);
//	while(1){
//	if(j==1){display(BluetoothGet()*8,5,l0);}
//	}
//}
*/

void Uart() interrupt 4
{
	/*接收部分*/
    a = SBUF;
    RI=0; // 接收中断标志位置0；
	/*发送部分*/
    SBUF = a;
    while(!TI);
    TI = 0;       // 发送中断标志位置0；
	/*选择标志部分*/
	if(i==0){i++;j=0;}
	else if (i>=1){i=0;j=1;}
}
