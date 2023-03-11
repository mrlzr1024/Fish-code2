/*
 * @Author: your name
 * @Date: 2021-12-10 12:50:49
 * @LastEditTime: 2021-12-10 13:22:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\GPIOBInit.h
 */
/*
 *名称：GPIOBInit(gpioboxInit)
 *用途：初始化管脚
 */
#ifndef __GPIOBINIT_H
#define __GPIOBINIT_H
#include "stm32f10x.h"
/*
 *函数名称：InitGPIO
 *输入: 1.*GPIOX //哪一组管脚 
        2.Iomode//IO口输出模式  
                     GPIO_Mode_AIN 
                     GPIO_Mode_IN_FLOATING 
                     GPIO_Mode_IPD 
                     GPIO_Mode_IPU 
                     GPIO_Mode_Out_OD 
                     GPIO_Mode_Out_PP 
                     GPIO_Mode_AF_OD 
                     GPIO_Mode_AF_PP
       3.pin//那一个管脚
                     GPIO_Pin_X
       4.Ioclock//IO口时钟
                     RCC_APB2Periph_AFIO             
                     RCC_APB2Periph_GPIOA            
                     RCC_APB2Periph_GPIOB              
                     RCC_APB2Periph_GPIOC           
                     RCC_APB2Periph_GPIOD              
                     RCC_APB2Periph_GPIOE            
                     RCC_APB2Periph_GPIOF            
                     RCC_APB2Periph_GPIOG            
                     RCC_APB2Periph_ADC1             
                     RCC_APB2Periph_ADC2            
                     RCC_APB2Periph_TIM1              
                     RCC_APB2Periph_SPI1               
                     RCC_APB2Periph_TIM8             
                     RCC_APB2Periph_USART1            
                     RCC_APB2Periph_ADC3             
                     RCC_APB2Periph_TIM15              
                     RCC_APB2Periph_TIM16              
                     RCC_APB2Periph_TIM17              
                     RCC_APB2Periph_TIM9               
                     RCC_APB2Periph_TIM10              
                     RCC_APB2Periph_TIM11              
       5.Iospeed//频率
                     GPIO_Speed_10MHz
                     GPIO_Speed_2MHz 
                     GPIO_Speed_50MHz

 *输出：无
 *备注：无
 */
extern void InitGPIO(GPIO_TypeDef *GPIOX,GPIOMode_TypeDef Iomode,uint16_t pin,uint32_t Ioclock,GPIOSpeed_TypeDef Iospeed);

#endif // !
