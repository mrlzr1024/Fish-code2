/*
 * @Author: your name
 * @Date: 2022-03-26 09:25:14
 * @LastEditTime: 2022-06-14 08:02:19
 * @LastEditors: MrLZR
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\My_USART.h
 */
#ifndef __MY_USART_H
#define __MY_USART_H

#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
#include <math.h>
#include <stdio.h>

//*********支持中文*********//
#pragma diag_suppress 77,550,1294,1295
#pragma diag_suppress 870
//*********支持中文*********//


extern u8 sbuf;
extern u8 input[20];
extern void My_Usart_Init(USART_InitTypeDef USART0, NVIC_InitTypeDef NVIC0);
extern void send(uint16_t Data);
#endif
