/*
 * @Author: your name
 * @Date: 2022-03-26 09:25:14
 * @LastEditTime: 2022-03-26 09:34:41
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\My_USART.h
 */
#ifndef __MY_USART_H
#define __MY_USART_H

#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"

extern 	u8 sbuf;
extern void My_Usart_Init(USART_InitTypeDef USART0,NVIC_InitTypeDef NVIC0);

#endif
