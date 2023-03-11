/*
 * @Author: your name
 * @Date: 2022-03-26 10:59:25
 * @LastEditTime: 2022-04-02 19:59:35
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\Car.c
 */
#include "Car.h"
int pin_A = 0;
int pin_B = 0;
int pin_C = 0;
int pin_D = 0;
void Init_Car(int pin_a, int pin_b, int pin_c, int pin_d)
{
	pin_A = pin_a;
	pin_B = pin_b;
	pin_C = pin_c;
	pin_D = pin_d;
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_a], F_50MHZ);
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_b], F_50MHZ);
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_c], F_50MHZ);
	LZR_GPIO_OUT(RB, GPIOB, LZR_PIN[pin_d], F_50MHZ);
	LZR_GPIO_OUT(RC, GPIOC, LZR_PIN[13], F_50MHZ);
}
void forward(int num, int Deviation)
{
	if (num + Deviation > 1000)
	{
		TIM_SetCompare1(TIM2, 1000);
		TIM_SetCompare2(TIM2, 0);
	}
	else
	{
		TIM_SetCompare1(TIM2, num + Deviation);
		TIM_SetCompare2(TIM2, 0);
	}
	if (num - Deviation < 0)
	{
		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare4(TIM2, 0);
	}
	else
	{
		TIM_SetCompare3(TIM2, num - Deviation);
		TIM_SetCompare4(TIM2, 0);
	}
}
void left(int num)
{
	TIM_SetCompare1(TIM2, num);
	TIM_SetCompare2(TIM2, 0);
	TIM_SetCompare3(TIM2, 0);
	TIM_SetCompare4(TIM2, num);
}
void right(int num)
{
	TIM_SetCompare1(TIM2, 0);
	TIM_SetCompare2(TIM2, num);
	TIM_SetCompare3(TIM2, num);
	TIM_SetCompare4(TIM2, 0);
}
void back(int num, int Deviation)
{
	if (num + Deviation > 1000)
	{
		TIM_SetCompare1(TIM2, 0);
		TIM_SetCompare2(TIM2, 1000);
	}
	else
	{
		TIM_SetCompare1(TIM2, 0);
		TIM_SetCompare2(TIM2, num + Deviation);
	}
	if (num - Deviation < 0)
	{
		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare4(TIM2, 0);
	}
	else
	{
		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare4(TIM2, num - Deviation);
	}
}
void stop(void)
{
	TIM_SetCompare1(TIM2, 0);
	TIM_SetCompare2(TIM2, 0);
	TIM_SetCompare3(TIM2, 0);
	TIM_SetCompare4(TIM2, 0);
}
