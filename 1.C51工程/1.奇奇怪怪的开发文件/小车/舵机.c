/*
 * @Author: your name
 * @Date: 2021-11-09 10:15:07
 * @LastEditTime: 2021-11-22 07:29:28
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \定时器中断控制舵机\舵机.c
 */
#include <reg51.h>
//sbit M0 = P2 ^ 0;
sbit a1 = P2 ^ 1;
//sbit a2 = P2 ^ 2;
//sbit a3 = P2 ^ 3;
void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x0FF;
    TL0 = 0x0D2;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void main(void)
{
	int T=1000;
    InitTimer0();
	while(1)
		if(TL0<=0XE9){
			a1=1;
		}
		else if(TL0>=0XE9&&TL0<=0XFF)
		{
		a1=0;
		}
//		else {
//		TH0 = 0;
//    TL0 =0;
	;
		}
//}

void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x0FF;
    TL0 = 0x0D2;
//	a1=~a1;
}

//void move(int mod,int U) //哪一位--mod
//{
//	T =500+ U;
//	TMOD = 0x01;
//	TH0 = 0;
//	TL0 = 0;
//	EA = 1;
//	ET0 = 1;
//	TR0 = 1;
//	while (TL0 + TH0 * 256 < T)
//	{
//		if(mod==0){M0 = 1;}
//		else if(mod==1){a1 = 1;}
//		else if(mod==2){a2 = 1;}
//		else if(mod==3){a3 = 1;}
//	}
//	while (TL0 + TH0 * 256 >= T && TL0 + TH0 * 256 <= 20000)
//	{
//		if(mod==0){M0 = 0;}
//		else if(mod==1){a1 = 0;}
//		else if(mod==2){a2 = 0;}
//		else if(mod==3){a3 = 0;}
//	}
//	TR0 = 0;
//}

//void main(void)
//{
//	int i = 0;
//	int j = 0;
//	while (1)
//	{
////		for (j = 0; j < 2; j++)
//		{
//			move(0,i);
//		}
//		i+=20;
//		if (i > 2000)
//		{
//			i = 0;
//		}
//	}
//}

//void Timer0Interrupt(void) interrupt 1
//{
//	TR0 = 0;
//}
