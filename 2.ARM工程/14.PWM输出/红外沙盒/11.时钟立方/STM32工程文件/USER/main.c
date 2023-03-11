/*
 * @Author: LZR
 * @Date: 2021-12-05 20:17:05
 * @LastEditTime: 2021-12-25 22:58:41
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
#include "spi.h"
#include "CharCode.h"
#include "TIMER_Init.h"
#include "sys.h"
#include "USARTer.h"
#include "RED.h"
#define respons 6 //回应的位GPIOAx
/*自定义界面*/
/*总初始化*/
// void SumInit(void)
// {
//     Stm32_Clock_Init(9); //系统时钟：8*9=72
//     delay_init(72);
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//     InitGPIO(1, 50, GPIOA);
//     InitGPIO(2, 50, GPIOA);
//     InitGPIO(3, 50, GPIOA);
//     InitGPIO(4, 50, GPIOA);
//     InitGPIO(5, 50, GPIOA);
//     InitGPIO(respons, 50, GPIOA); //背光板正极,回应位
//                                   /*初始化待机系统*********************************/
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//     InitGPIO(0, 50, GPIOB);
//     /*电源**************************************/
//     LCD_init();
//     TIMER_Init(9999, 7199);
//     EXTIInit(); //<<<======
//     USART_Init1();
//     /*初始化函数**********************************/
//     PAout(respons) = 0;
//     LCD_draw_bmp_pixel(0, 0, CLKmode[2], 84, 48);
//     delay_ms(1000);
//     LCD_clear();
// }
void Tinit(int arr, int psc)
{
    TIM_OCInitTypeDef OCI;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    GPIOInit(GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_7, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    TIMER_Init(arr, psc);
    OCI.TIM_OCMode = TIM_OCMode_PWM2;
    OCI.TIM_OutputState = TIM_OutputState_Enable;
    OCI.TIM_Pulse = 100;
    OCI.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OC2Init(TIM3, &OCI);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_Cmd(TIM3, ENABLE);
    // TIM_SetCompare2(TIM3, 899);
}
int main(void)
{
    u16 led = 0;
    u8 dir = 1;
    Stm32_Clock_Init(9);
    delay_init(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
       Tinit(899,0);
    // GPIOInit(GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_7, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
    // PAout(7) = 1;
    while (1)
    {
        delay_ms(5);
        if (dir)
        {
            led++;
        }
        else
        {
            led--;
        }

        if (led > 500)
        {
            dir = 0;
        }
        if (led == 0)
        {
            dir = 1;
        }
        TIM_SetCompare2(TIM3, led);
    }
}


