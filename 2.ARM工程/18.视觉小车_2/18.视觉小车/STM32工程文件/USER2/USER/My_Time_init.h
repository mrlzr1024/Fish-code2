/*
 * @Descripttion: your project
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-13 19:12:00
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-13 20:41:33
 */
#ifndef __MY_TIME_INIT_H
#define __MY_TIME_INIT_H

#include "stm32f10x.h"
#define ENCODER_TIM_PERIOD (u16)(65535) 
//右电机编码器计数
//PA15----接 编码器A相 或者电机驱动的B1A标识
//PB3 ----接 编码器B相 或者电机驱动的B1B标识
//左电机编码器计数
//PB4----接 编码器A相 或者电机驱动的B2A标识
//PB5----接 编码器B相 或者电机驱动的B2B标识
extern void Encoder_Init_TIM2(void);
extern void Encoder_Init_TIM3(void);
extern void Encoder_Start(void);
extern int Read_Encoder(u8 TIMX);


#endif

