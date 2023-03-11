/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2022-06-15 15:13:20
 * @LastEditors: MrLZR
 * @Description: ??koroFileHeader???? ????: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "My_USART.h"

u8 sbuf;
u8 input[20];
int length = 0;

void My_Usart_Init(USART_InitTypeDef USART0, NVIC_InitTypeDef NVIC0)
{
	GPIO_InitTypeDef GPIOBX;
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/******************************************************************/
	GPIOBX.GPIO_Mode = GPIO_Mode_AF_PP; //???
	GPIOBX.GPIO_Pin = GPIO_Pin_9;		// A9
	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOBX); // GPIOA???
	/******************************************************************/
	GPIOBX.GPIO_Mode = GPIO_Mode_IN_FLOATING; //???
	GPIOBX.GPIO_Pin = GPIO_Pin_10;
	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOBX); // GPIOA???
	/******************************************************************/
	USART0.USART_BaudRate = 115200;
	USART0.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART0.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART0.USART_Parity = USART_Parity_No;
	USART0.USART_StopBits = USART_StopBits_1;
	USART0.USART_WordLength = USART_WordLength_8b;
	USART_Cmd(USART1, ENABLE);
	/******************************************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //??
	USART_Init(USART1, &USART0);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/******************************************************************/
	NVIC0.NVIC_IRQChannel = USART1_IRQn;
	NVIC0.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC0.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC0);
}
/*发送字符
Data:(uint16_t) 要发送的字符
void
*/
void send(uint16_t Data)
{
	USART_SendData(USART1, Data); //向串口1，发送一个字符
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
		; //等待发送完成
}
/*将数组转化为数字
void
void
*/
int translate(void)
{
	int k, n, Switch = 0, num = 0;
	for (n = length - 3, k = 2; k < length; k++, n--)
	{
		if (input[k] == '-')
		{
			k++;
			n--;
			Switch = 1;
		}
		num += (input[k] - '0') * pow(10, n);
	}
	if (Switch)
	{
		num = -num;
	}
	return num;
}
/*截取输入的前10个字符('\n'作为结尾)
 */
void USART1_IRQHandler(void)
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		sbuf = USART_ReceiveData(USART1);
		if (sbuf != '\n')
		{
			input[length++] = sbuf;
		}
		if (length >= 10 || sbuf == '\n') // max=10
		{
			length = 0;
		}
		send(sbuf);
	}
	USART_ClearFlag(USART1, USART_FLAG_RXNE); //清空中断标志位
}
/***支持printf函数***/




#pragma import(__use_no_semihosting)
void _sys_exit(int x)
{
	x = x;
}
struct __FILE
{
	int handle;
};
FILE __stdout;
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (unsigned char) ch);
	while (!(USART1->SR & USART_FLAG_TXE));
	return (ch);
}


/***支持printf函数***/
