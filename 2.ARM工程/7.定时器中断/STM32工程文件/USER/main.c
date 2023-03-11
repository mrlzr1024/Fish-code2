/*
 * @Author: your name
 * @Date: 2021-12-05 20:17:05
 * @LastEditTime: 2021-12-05 21:23:15
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "GPIOBInit.h"
int i=0;
void Timer_init(u16 arr,u16  psc)
{
	TIM_TimeBaseInitTypeDef TIMER;
	NVIC_InitTypeDef NVIC0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/*****************Step1**********************************/
	TIMER.TIM_Period = arr;
	TIMER.TIM_Prescaler = psc;
	TIMER.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMER.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIMER);
	/********************Step2*******************************/
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
	NVIC0.NVIC_IRQChannel=TIM3_IRQn;
	NVIC0.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC0.NVIC_IRQChannelSubPriority = 3;
	NVIC0.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC0);
	/********************Step3*******************************/
	TIM_Cmd(TIM3, ENABLE);
}
/********************Step3*******************************/
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		if(i%2==0){
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);}
		else if(i%2==1){
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
		}
		i++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		if(i>=100){i=0;}
	}
}
/********************Step-anthor*******************************/
/********************Step-END*******************************/

int  main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(64);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //GPIOA
	InitGPIO(0,50,GPIOA);
		InitGPIO(1,50,GPIOA);
	Timer_init(999, 1199);
					GPIO_SetBits(GPIOA,GPIO_Pin_0);

	while (1){
				GPIO_ResetBits(GPIOA,GPIO_Pin_1);
				delay_ms(100);
				GPIO_SetBits(GPIOA,GPIO_Pin_1);
				delay_ms(100);

	}

}



