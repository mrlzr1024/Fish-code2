/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2021-12-05 17:38:32
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */

#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"

typedef unsigned int u16;
typedef unsigned char u8;
// delay_us
// sbit SRCLK=P3^6;
// sbit RCLK=P3^5;
// sbit SER=P3^4;

u8 ledduan[] = {0x00, 0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e, 0x00};
u8 ledwei[] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};
void _nop_(void){delay_us(1);}
void delay(u16 i)
{
	while (i--)
		;
}

void Hc595SendByte(u8 dat)
{
	u8 a;
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	// SRCLK=0;	// sbit SRCLK=P3^6;			
	// RCLK=0;	// sbit RCLK=P3^5;
	for (a = 0; a < 8; a++)
	{
		if(dat>>7==1){GPIO_SetBits(GPIOB, GPIO_Pin_4);}
		else if(dat>>7==0){GPIO_ResetBits(GPIOB, GPIO_Pin_4);}
		// SER=dat>>7;// sbit SER=P3^4;
		dat <<= 1;
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		// SRCLK=1;	// sbit SRCLK=P3^6;		
		_nop_();
		_nop_();
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		// SRCLK = 0;	// sbit SRCLK=P3^6;		
	}
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	// RCLK=1;	// sbit RCLK=P3^5;
	_nop_();
	_nop_();
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	// RCLK=0;	// sbit RCLK=P3^5;
}

void main()
{
	u8 i;
	char ii;
	GPIO_InitTypeDef GPIOBX;
	delay_init(64);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // GPIOA
	GPIOBX.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOBX.GPIO_Pin = GPIO_Pin_All; // A-ALL
	GPIOBX.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOBX); // GPIOA初始化
	InitGPIO(4, 50, GPIOB);
	InitGPIO(5, 50, GPIOB);
	InitGPIO(6, 50, GPIOB);

	while (1)
	{
		// P0=0x7f;
		
		for (i = 0; i < 8; i++)
		{
			ii=0x01;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x02;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x04;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x08;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x10;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x20;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x40;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}

			ii=0x80;
			if(ledwei[i]&ii==1){GPIO_SetBits(GPIOA, GPIO_Pin_0);}
			else if(ledwei[i]&ii==0){GPIO_ResetBits(GPIOA, GPIO_Pin_0);}
			// P0=ledwei[i];		 
			Hc595SendByte(ledduan[i]); //·¢ËÍ¶ÎÑ¡Êý¾Ý
			delay(100);				   //ÑÓÊ±
			Hc595SendByte(0x00);	   //ÏûÒþ
		}
	}
}

/*
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"

int main(void)
{
		GPIO_InitTypeDef GPIOBX;
		delay_init(64);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //GPIOA
		GPIOBX.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIOBX.GPIO_Pin =GPIO_Pin_All; //A-ALL
		GPIOBX.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIOBX); //GPIOA初始化

	while (1)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);

		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_1);

		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_2);

		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_3);

		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);

		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);

		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);

		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
	}
}
*/