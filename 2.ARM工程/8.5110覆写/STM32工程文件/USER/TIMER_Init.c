/*
 * @Author: your name
 * @Date: 2021-12-07 09:34:31
 * @LastEditTime: 2021-12-07 10:33:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\TIMER_Init.c
 */
#include "TIMER_Init.h"
int i = 0;
int hour = 0, minuse = 0, second = 0;
void TIMER_Init(int arr, int psc)
{
    TIM_TimeBaseInitTypeDef TIMER;
    NVIC_InitTypeDef NVIC0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /*_________________________________________________________*/
    TIMER.TIM_Period = arr;
    TIMER.TIM_Prescaler = psc;
    TIMER.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIMER);
    /*_________________________________________________________*/
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC0.NVIC_IRQChannel = TIM3_IRQn;
    NVIC0.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC0.NVIC_IRQChannelSubPriority = 2;
    NVIC0.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC0);
    /*_________________________________________________________*/
    TIM_Cmd(TIM3, ENABLE);
    /*_________________________________________________________*/
}
void TIM3_IRQHandler(void)
{

    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        i++;
        if (i >= 60)
        {
            i = 0;
        }
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
    second = i;
    if (second == 59)
    {
        minuse++;
        if (minuse > 59)
        {
            minuse = 0;
            hour++;
            if (hour >= 24)
            {
                hour = 0;
            }
        }
    }
}
