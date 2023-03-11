/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2022-04-21 14:18:54
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "My_USART.h"
#include "sys.h"
#include "Car.h"
#include "time.h"
int main(void)
{
	int i=0;
	Stm32_Clock_Init(9);
	delay_init(72);
	LZR_GPIO_OUT(RCC_APB2Periph_GPIOB,GPIOB,12,F_50MHZ);
	LZR_init_PWM(999,1439);//duty=[0:1000]
	PBout(12) = 0;
	delay_ms(200);
	//i=[25:125];
	// TIM_SetCompare1(TIM2, 25);
	// delay_ms(200);
	TIM_SetCompare2(TIM2, 25);
	TIM_SetCompare1(TIM2, 100);
	// delay_ms(200);
	// TIM_SetCompare3(TIM2, 25);
	// delay_ms(200);
	// TIM_SetCompare4(TIM2, 25);
	// delay_ms(200);
	while (1)
	{

		PBout(12) = 0;
		delay_ms(50);
		PBout(12) = 1;
		delay_ms(50);
	}
}


