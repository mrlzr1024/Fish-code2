/*
 * @Author: your name
 * @Date: 2022-03-26 11:15:30
 * @LastEditTime: 2022-03-26 11:50:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\My_GPIO.h
 */
#ifndef  __MY_GPIO_H
#define  __MY_GPIO_H
#include "stm32f10x.h"
/*时钟****************************************************************************************/
#define RO RCC_APB2Periph_AFIO
#define RA RCC_APB2Periph_GPIOA
#define RB RCC_APB2Periph_GPIOB
#define RC RCC_APB2Periph_GPIOC
#define RD RCC_APB2Periph_GPIOD
#define RE RCC_APB2Periph_GPIOE
#define RF RCC_APB2Periph_GPIOF
#define RG RCC_APB2Periph_GPIOG
/*管脚******************************************************************************************/
extern uint16_t LZR_PIN[];

/*频率**********************************************************************************************/
#define F_50MHZ GPIO_Speed_50MHz
#define F_10MHZ GPIO_Speed_10MHz
#define F_2MHZ GPIO_Speed_2MHz


extern void LZR_GPIO_OUT(uint32_t RCC_X, GPIO_TypeDef *GPIOX,uint16_t pin, GPIOSpeed_TypeDef frequency);
extern void LZR_GPIO_IN(uint32_t RCC_X, GPIO_TypeDef *GPIOX,uint16_t pin, GPIOSpeed_TypeDef frequency);
#endif


