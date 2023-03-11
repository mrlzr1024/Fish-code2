/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2022-03-26 11:45:43
 * @LastEditors: Please set LastEditors
 * @Description: ??koroFileHeader???? ????: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "My_USART.h"
u8 sbuf;
void My_Usart_Init(USART_InitTypeDef USART0,NVIC_InitTypeDef NVIC0)
{
	GPIO_InitTypeDef GPIOBX;
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	/******************************************************************/
	GPIOBX.GPIO_Mode = GPIO_Mode_AF_PP; //???
	GPIOBX.GPIO_Pin = GPIO_Pin_9;		//A9
	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOBX); //GPIOA???
	/******************************************************************/
	// GPIOBX.GPIO_Mode = GPIO_Mode_Out_PP; //???
	// GPIOBX.GPIO_Pin = GPIO_Pin_12;		//A9
	// GPIOBX.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_Init(GPIOB, &GPIOBX); //GPIOA???
	/******************************************************************/
	GPIOBX.GPIO_Mode = GPIO_Mode_IN_FLOATING; //???
	GPIOBX.GPIO_Pin = GPIO_Pin_10;			  //A10
	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIOBX); //GPIOA???
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
