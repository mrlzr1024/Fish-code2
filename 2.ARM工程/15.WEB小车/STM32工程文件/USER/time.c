/*
 * @Author: your name
 * @Date: 2022-03-27 11:20:28
 * @LastEditTime: 2022-03-28 20:17:39
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\time.c
 */
#include "time.h"
void LZR_init_PWM(int arr, int psc)
{
    TIM_OCInitTypeDef OCI;
    TIM_TimeBaseInitTypeDef TIMER;
    GPIO_InitTypeDef GPIO;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_0;
    //定时器TIM2的PWM输出通道1，2，3，4；TIM2,CH2,CH3,CH1,CH4.
    GPIO.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO); //初始化GPIO

    TIMER.TIM_Period = arr;
    TIMER.TIM_Prescaler = psc;
    TIMER.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM2, &TIMER);

    OCI.TIM_OCMode = TIM_OCMode_PWM2;
    OCI.TIM_OutputState = TIM_OutputState_Enable;
    OCI.TIM_Pulse = 100;
    OCI.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC3Init(TIM2, &OCI); //初始化CH3通道
    TIM_OC2Init(TIM2, &OCI); //初始化CH2通道
    TIM_OC1Init(TIM2, &OCI); //初始化CH1通道
    TIM_OC4Init(TIM2, &OCI); //初始化CH4通道
    TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_Cmd(TIM2, ENABLE);
}
/*********************************************************************************/

void LZR_init_PWM_test(TIM_TypeDef *TIMX,
                    uint32_t RCC_APB2Periph_GPIOX,
                    GPIO_TypeDef *GPIOX,
                    uint16_t GPIO_Pin_x,
                    int arr,
                    int psc)
{
    TIM_OCInitTypeDef OCI;
    TIM_TimeBaseInitTypeDef TIMER;
    GPIO_InitTypeDef GPIO;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOX, ENABLE);

    GPIO.GPIO_Pin = GPIO_Pin_x;
    //定时器TIM2的PWM输出通道1，2，3，4；TIM2,CH2,CH3,CH1,CH4.
    GPIO.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOX, &GPIO); //初始化GPIO

    TIMER.TIM_Period = arr;
    TIMER.TIM_Prescaler = psc;
    TIMER.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIMX, &TIMER);

    OCI.TIM_OCMode = TIM_OCMode_PWM2;
    OCI.TIM_OutputState = TIM_OutputState_Enable;
    OCI.TIM_Pulse = 100;
    OCI.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC3Init(TIMX, &OCI); //初始化CH3通道
    TIM_OC2PreloadConfig(TIMX, TIM_OCPreload_Enable);
    TIM_Cmd(TIMX, ENABLE);
}
