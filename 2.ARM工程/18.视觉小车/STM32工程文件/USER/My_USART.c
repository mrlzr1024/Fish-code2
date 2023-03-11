#include "My_USART.h"

//重定向C库函数printf到串口，重定向后可使用printf函数
int fputc(int ch,FILE *f)
{
	/* 发送一个字节数据到串口 */
	USART_SendData(USART1,(uint8_t) ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return (ch);
}

//重定向C库函数scanf到串口,重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
	/* 等待串口输入数据 */
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return (int)USART_ReceiveData(USART1);
}

void MyUSART_Init()
{
	/* 定义GPIO、NVIC和USART初始化的结构体 */
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能GPIO和USART的时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	/* 将USART TX（A9）的GPIO设置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/* 将USART RX（A10）的GPIO设置为浮空输入模式 */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	/* 配置串口 */
	USART_InitStructure.USART_BaudRate=115200;										//波特率了设置为115200
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//不使用硬件流控制
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;						//使能接收和发送
	USART_InitStructure.USART_Parity=USART_Parity_No;								//不使用奇偶校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;							//1位停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;						//字长设置为8位
	USART_Init(USART1, &USART_InitStructure);

	/* Usart1 NVIC配置 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//设置NVIC中断分组2
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);

	/*初始化串口，开启串口接收中断 */
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	/* 使能串口1 */
	USART_Cmd(USART1,ENABLE);

}





unsigned char input[20];
int i=0;
/* USART1中断函数 */
void USART1_IRQHandler(void)
{

	uint8_t ucTemp;
	//unsigned char ucTemp;										//接收数据
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		ucTemp = USART_ReceiveData(USART1);
		USART_SendData(USART1,ucTemp);
		input[i++]=ucTemp;

		if(i>=15||ucTemp=='\n'){
			i=0;
		}
	}
}

/* 发送一个字节 */
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);

	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/* 发送字符串 */
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');

  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}


























// /*
//  * @Author: your name
//  * @Date: 2021-12-03 19:48:24
//  * @LastEditTime: 2022-06-18 17:44:12
//  * @LastEditors: MrLZR
//  * @Description: ??koroFileHeader???? ????: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
//  * @FilePath: \USER\main.c
//  */
// #include "My_USART.h"

// u8 sbuf;
// u8 input[20];
// int length = 0;

// void My_Usart_Init(USART_InitTypeDef USART0, NVIC_InitTypeDef NVIC0)
// {
// 	GPIO_InitTypeDef GPIOBX;
// 	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
// 	/******************************************************************/
// 	GPIOBX.GPIO_Mode = GPIO_Mode_AF_PP; //???
// 	GPIOBX.GPIO_Pin = GPIO_Pin_9;		// A9
// 	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
// 	GPIO_Init(GPIOA, &GPIOBX); // GPIOA???
// 	/******************************************************************/
// 	GPIOBX.GPIO_Mode = GPIO_Mode_IN_FLOATING; //???
// 	GPIOBX.GPIO_Pin = GPIO_Pin_10;
// 	GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
// 	GPIO_Init(GPIOA, &GPIOBX); // GPIOA???
// 	/******************************************************************/
// 	USART0.USART_BaudRate = 115200;
// 	USART0.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
// 	USART0.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
// 	USART0.USART_Parity = USART_Parity_No;
// 	USART0.USART_StopBits = USART_StopBits_1;
// 	USART0.USART_WordLength = USART_WordLength_8b;
// 	USART_Cmd(USART1, ENABLE);
// 	/******************************************************************/
// 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //??
// 	USART_Init(USART1, &USART0);
// 	USART_Cmd(USART1, ENABLE);
// 	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
// 	/******************************************************************/
// 	NVIC0.NVIC_IRQChannel = USART1_IRQn;
// 	NVIC0.NVIC_IRQChannelPreemptionPriority = 0;
// 	NVIC0.NVIC_IRQChannelSubPriority = 1;
// 	NVIC_Init(&NVIC0);
// 	//printf("IN");
// }
// /*发送字符
// Data:(uint16_t) 要发送的字符
// void
// */
// void send(uint16_t Data)
// {
// 	USART_SendData(USART1, Data); //向串口1，发送一个字符
// 	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
// 		; //等待发送完成
// }
// int strlen(char* num){
// 	int len;
// 	while(num[len++]){
// 	}
// 	len--;
// 	return len;
// }
// /*将数组转化为数字
// void
// void
// */
// //int translate(char *num)
// //{
// //	{
// //		uint8_t siz = strlen(num);
// //		if (siz < 1)
// //			return 0;
// //		int8_t flag = 1;
// //		if (num[0] == '-')
// //			flag = -1;
// //		uint8_t res = 0;
// //		for (uint8_t i = (num[0] == '+' || num[0] == '-') ? 1 : 0; i < siz; i++)
// //		{
// //			if (num[i] < '0' || num[i] > '9')
// //				return 0;
// //			res = (res << 3) + (res << 1) + (num[i] & 0xf); //'0'和'9'低4位刚好是0～9
// //		}
// //		return flag * res;
// //	}
// //}
// /*截取输入的前10个字符('\n'作为结尾)
//  */
// void USART1_IRQHandler(void)
// {
// 	int i = 0;
// 	//printf("IN2");
// 	if (USART_GetITStatus(USART1, USART_IT_RXNE))
// 	{
// 		sbuf = USART_ReceiveData(USART1);
// 		if (sbuf != '\n')
// 		{
// 			input[i++] = sbuf;
// 		}
// 		if (i >= 10 || sbuf == '\n' || sbuf == '\r') // max=10
// 		{
// 			length = --i;
// 			i = 0;
// 		}
// 		send(sbuf);
// 	}
// 	USART_ClearFlag(USART1, USART_FLAG_RXNE); //清空中断标志位
// }
// /***支持printf函数***/

// #pragma import(__use_no_semihosting)
// void _sys_exit(int x)
// {
// 	x = x;
// }
// struct __FILE
// {
// 	int handle;
// };
// FILE __stdout;
// int fputc(int ch, FILE *f)
// {
// 	USART_SendData(USART1, (unsigned char)ch);
// 	while (!(USART1->SR & USART_FLAG_TXE))
// 		;
// 	return (ch);
// }

// /***支持printf函数***/
