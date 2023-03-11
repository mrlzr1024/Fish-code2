/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2021-12-12 21:01:20
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
#include "sys.h"
#include "usart.h"
void init_uart();
int  count=0;
void EXTIInit(void)
{
 NVIC_InitTypeDef NVIC1;
 EXTI_InitTypeDef EXTIa;
//	InitGPIO(GPIOB, GPIO_Mode_Out_PP, GPIO_Pin_12, RCC_APB2Periph_GPIOB, GPIO_Speed_50MHz);
//	InitGPIO(GPIOB, GPIO_Mode_IN_FLOATING, GPIO_Pin_0, RCC_APB2Periph_GPIOB, GPIO_Speed_50MHz);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	 Ex_NVIC_Config(GPIO_B, 0, 1); //	Ex_NVIC_Config()
//	 MY_NVIC_Init(2, 0, EXTI0_IRQn, 2);
	InitGPIO(GPIOA, GPIO_Mode_Out_PP, GPIO_Pin_1, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
	InitGPIO(GPIOD, GPIO_Mode_IN_FLOATING, GPIO_Pin_0, RCC_APB2Periph_GPIOD, GPIO_Speed_50MHz);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource0);
	//=/
	EXTIa.EXTI_Line = EXTI_Line0;
	EXTIa.EXTI_LineCmd = ENABLE;
	EXTIa.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTIa.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTIa);
	//=/
	NVIC1.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC1.NVIC_IRQChannelCmd = ENABLE;
	NVIC1.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC1.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC1);
	//=/

}
void EXTI0_IRQHandler(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) //确认是否真的接收到正确的信号
	{
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
			PBout(12) = !PBout(12);
			count++;
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}



int main(void)
{
	Stm32_Clock_Init(9);
	delay_init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
	InitGPIO(GPIOA, GPIO_Mode_Out_PP, GPIO_Pin_0, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
	init_uart();
	EXTIInit();
	PAout(1) = 1;
	while (1)
	{
		USART_SendData(USART1, count);
	}
}

void USART1_IRQHandler(void)
{
	u8 a;
	if (USART_GetITStatus(USART1, USART_IT_RXNE))
	{
		a = USART_ReceiveData(USART1);
		USART_SendData(USART1, a);
	}
}


void init_uart(){

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
//	while (1)
//		;

}