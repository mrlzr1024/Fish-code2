/*
 * @Author: your name
 * @Date: 2021-12-07 17:18:41
 * @LastEditTime: 2021-12-14 08:22:56
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\USART.h
 */
#ifndef __USARTER_H
#define __USARTER_H
#include "stm32f10x.h"
extern void USART_Init1(void);
extern u8 a;
extern void USART1_IRQHandler(void);
#endif // !__USART_H
