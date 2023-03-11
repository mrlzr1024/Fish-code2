/*
 * @Author: your name
 * @Date: 2021-12-22 21:10:07
 * @LastEditTime: 2021-12-23 08:57:48
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
#include "usart.h"
#include "sys.h"
#define uchar unsigned char
#define uint unsigned int
#define RS PBout(1) // P2^6;
#define RW PBout(2) //=P2^5;
#define EN PBout(0) //=P2^7;
#define P0 GPIOA->ODR = 0x00 | (u8)
uchar com;
void delay(uint z)
{
	delay_ms(z);
}
void write_com(uchar com)
{
	RS = 0;
	RW = 0;
	P0 com;
	delay(5);
	EN = 1;
	delay(5);
	EN = 0;
}
void write_data(char date)
{
	RS = 1;
	P0 date;
	delay(5);
	EN = 1;
	delay(5);
	EN = 0;
}
uchar table1[] = {0x10, 0x06, 0x09, 0x08, 0x08, 0x09, 0x06, 0x00};	//字符℃
uchar table4[] = {0xF7, 0xAB, 0xCB, 0x00, 0x3E, 0x08, 0x08, 0x7F};	//字符
uchar table5[] = {0x00, 0x0E, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00};	//字符二
uchar table6[] = {0x0E, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x1F, 0x00};	//字符三
uchar table7[] = {0x1F, 0x11, 0x15, 0x15, 0x1F, 0x11, 0x1F, 0x00};	//字符四
uchar table8[] = {0x1E, 0x08, 0x08, 0x1E, 0x0A, 0x0A, 0x1F, 0x00};	//字符五
uchar table9[] = {0x08, 0x1F, 0x12, 0x0F, 0x0A, 0x1F, 0x02, 0x00};	//字符年
uchar table10[] = {0x0F, 0x09, 0x0F, 0x09, 0x0F, 0x09, 0x13, 0x00}; //字符月
uchar table11[] = {0x1F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F, 0x00}; //字符日
void init()
{
	int i = 0;
	EN = 0;
	write_com(0x38);
	write_com(0x0e);
	write_com(0x06);
	write_com(0x40); //
	for (i = 0; i <= 8; i++)
	{
		write_data(table4[i]);
	}
	write_com(0x80);
}
int main()
{
//	int u = 0, i = 0;
	Stm32_Clock_Init(9);
	delay_init(72);
	GPIOInit(GPIOA, GPIO_Mode_Out_PP, GPIO_Pin_All, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	InitGPIO(0, 50, GPIOB);
	InitGPIO(1, 50, GPIOB);
	InitGPIO(2, 50, GPIOB);
	uart_init(72, 115200);
	init();
	delay(6);
	write_data('A');
	delay(20);
	write_com(0x81 + 1);
	write_data(0x00);
	while (1)
	{
				printf("请输入指令：");
			write_data(USART_RX_BUF[0]);
//		for (u = 0; u < 8; u++)
//		{
//			table11[u] = USART_RX_BUF[0];
//		}
//		write_com(0x40); //
//		for (i = 0; i <= 8; i++)
//		{
//			write_data(table11[i]);
//		}
		printf("好的  ");
		write_com(0x81 + 1);
		write_data(0x00);
	}
}

