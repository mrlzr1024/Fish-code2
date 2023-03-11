/*
 * @Author: your name
 * @Date: 2021-10-30 08:20:22
 * @LastEditTime: 2021-12-06 19:16:30
 * @LastEditors: Please set LastEditors
 * @Description: ��koroFileHeader�鿴���� ��������: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
int main()
{
	delay_init(64);
	LED_Init();
	while (1)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5); // A5����ߵ�ƽ
		GPIO_SetBits(GPIOB, GPIO_Pin_12); // B12����ߵ�ƽ
		delay_ms(5);

		GPIO_ResetBits(GPIOA, GPIO_Pin_5);	// A5����͵�ƽ
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); // B12����͵�ƽ
		delay_ms(50);
	}
}
