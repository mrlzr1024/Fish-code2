/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2021-12-05 16:39:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
void USART1_IRQHandler(void)
{
	u8 a;
	if (USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		a = USART_ReceiveData(USART1);
		USART_SendData(USART1, a);
	}
}
int main(void)
{
	GPIO_InitTypeDef GPIOBX;
	USART_InitTypeDef USART0;
	NVIC_InitTypeDef NVIC0;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/******************************************************************/
	GPIOBX.GPIO_Mode = GPIO_Mode_AF_PP; //输出脚
	GPIOBX.GPIO_Pin = GPIO_Pin_9;		//9
	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOBX); //GPIOB初始化
	/******************************************************************/
	GPIOBX.GPIO_Mode = GPIO_Mode_IN_FLOATING; //输出脚
	GPIOBX.GPIO_Pin = GPIO_Pin_10;			  //9
	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOBX); //GPIOB初始化
	/******************************************************************/
	USART0.USART_BaudRate = 115200;
	USART0.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART0.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART0.USART_Parity = USART_Parity_No;
	USART0.USART_StopBits = USART_StopBits_1;
	USART0.USART_WordLength = USART_WordLength_8b;
	USART_Cmd(USART1, ENABLE);
	/******************************************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //分组
	USART_Init(USART1, &USART0);
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/******************************************************************/
	NVIC0.NVIC_IRQChannel = USART1_IRQn;
	NVIC0.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC0.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC0);
	while (1)
		;
}
