/*
 * @Author: your name
 * @Date: 2022-03-26 09:08:22
 * @LastEditTime: 2022-04-02 20:26:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "main.h"

int i = 0;
u8 input[20];
int length = 0;
int translate(void);
void send(uint16_t Data);

int main(void)
{
	USART_InitTypeDef USART0;
	NVIC_InitTypeDef NVIC0;
	int deviation=0;//偏向角
	Stm32_Clock_Init(9); //倍频系数：9
	delay_init(72);		 //系统时钟:72MHZ
	Init_Car(1, 2, 3, 4);
	LZR_init_PWM(999, 712);
	My_Usart_Init(USART0, NVIC0); //使用:第1组USART
	PCout(13) = 0;
	delay_ms(200);
	while (1)
	{
		if (input[1] != '=')
		{
			PCout(13) = 1;
			continue;
		}
		switch (input[0])
		{
		case 'f':
		forward(translate(),deviation);
			break;
		case 'l':
		left(translate());
			break;
		case 'r':
		right(translate());
			break;
		case 'b':
		back(translate(),deviation);
			break;
		case 's':
		stop();
			break;
		case 'd'://向左偏
		deviation=translate();
			break;
		default:
			break;
		}
		PCout(13) = 0;
		// TIM_SetCompare2(TIM2, translate());
	}
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
	int k, n,Switch=0, num = 0;
	for (n = length - 3, k = 2; k < length; k++, n--)
	{
		if(input[k]=='-'){
			k++;
			n--;
			Switch=1;
		}
		num += (input[k] - '0') * pow(10, n);
	}
	if(Switch){
		num=-num;
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
			input[i++] = sbuf;
		}
		if (i >= 10 || sbuf == '\n')
		{
			i = 0;
		}
		if (i != 0)
		{
			length = i - 1;
			send(length);
		}
	}
	USART_ClearFlag(USART1, USART_FLAG_RXNE); //清空中断标志位
}
