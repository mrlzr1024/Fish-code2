/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2022-06-12 16:55:32
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"

int main(void)
{
		GPIO_InitTypeDef GPIOBX;
	Stm32_Clock_Init(9);
		delay_init(72);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //GPIOA
		GPIOBX.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIOBX.GPIO_Pin =GPIO_Pin_All; //A-ALL
		GPIOBX.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIOBX); //GPIOA初始化

		GPIO_SetBits(GPIOA, GPIO_Pin_All);
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
		delay_ms(100);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_6);

		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		delay_ms(100);
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
	}
}
