/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2022-03-28 13:38:56
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "My_USART.h"
#include "sys.h"
#include "Car.h"
#include "time.h"
void PWM_Init(void)
{
	GPIO_InitTypeDef 			GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  			TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 ;
	//定时器TIM2的PWM输出通道2,3,4，TIM2,CH2,3,4.
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    //定时器TIM3的PWM输出通道1,2  TIM3,CH1,2。
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO

	TIM_TimeBaseStructure.TIM_Period = 999;//自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler =719; //时钟预分频数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化TIM4

	TIM_TimeBaseStructure.TIM_Period = 999;//自动重装值
	TIM_TimeBaseStructure.TIM_Prescaler =719; //时钟预分频数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //初始化TIM4

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0; //
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出极性为高
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);//初始化TIM2_CH2
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);//初始化TIM2_CH3
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);//初始化TIM2_CH4
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);//初始化TIM3_CH1
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);//初始化TIM3_CH2

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//OC1
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//OC2
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//OC3
    TIM_ARRPreloadConfig(TIM2, ENABLE); //使能重装寄存器

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//OC4
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//OC5
	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能重装寄存器

	TIM_Cmd(TIM2, ENABLE);//使能定时器TIM2，准备工作
	TIM_Cmd(TIM3, ENABLE);//使能定时器TIM3，准备工作
}
int main(void)
{
	u16 led = 0;
	u8 dir = 1;
	Stm32_Clock_Init(9);
	delay_init(72);
	LZR_init_PWM(999,7);
	PCout(13) = 1;
	delay_ms(200);
	while (1)
	{
//		delay_ms(5);
//		if (dir)
//		{
//			led++;
//		}
//		else
//		{
//			led--;
//		}

//		if (led > 500)
//		{
//			dir = 0;
//		}
//		if (led == 0)
//		{
//			dir = 1;
//		}
		TIM_SetCompare1(TIM2, 25);
		TIM_SetCompare2(TIM2, 25);
		TIM_SetCompare3(TIM2, 25);
		TIM_SetCompare4(TIM2, 25);
	}
}
// void cell_back(u8 info){
// 	if(info=='f'){
// 		forward();
// 		}
// 	else if(info=='l'){
// 		left();
// 		}
// 	else if(info=='r'){
// 		right();
// 		}
// 	else if(info=='b'){
// 		back();
// 		}
// }
/*串口中断*******************************************************************************/
// void USART1_IRQHandler(void)
// {
// 	if (USART_GetITStatus(USART1, USART_IT_RXNE))
// 	{
// 		sbuf = USART_ReceiveData(USART1);
// 		USART_SendData(USART1, sbuf);
// 		if(sbuf=='a'){
// 		PBout(12) = 1;
// 		}
// 		else if (sbuf=='b'){
// 		PBout(12) = 0;
// 		}
// 		cell_back(sbuf);
// 	}
// }
/*串口中断*******************************************************************************/
