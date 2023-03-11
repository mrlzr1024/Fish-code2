/*
 * @Author: your name
 * @Date: 2021-10-30 08:20:22
 * @LastEditTime: 2021-12-06 19:16:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
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
		GPIO_SetBits(GPIOA, GPIO_Pin_5); // A5输出高电平
		GPIO_SetBits(GPIOB, GPIO_Pin_12); // B12输出高电平
		delay_ms(5);

		GPIO_ResetBits(GPIOA, GPIO_Pin_5);	// A5输出低电平
		GPIO_ResetBits(GPIOB, GPIO_Pin_12); // B12输出低电平
		delay_ms(50);
	}
}
