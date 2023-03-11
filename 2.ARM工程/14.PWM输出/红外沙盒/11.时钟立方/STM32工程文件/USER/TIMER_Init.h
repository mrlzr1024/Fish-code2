/*
 * @Author: your name
 * @Date: 2021-12-07 09:34:45
 * @LastEditTime: 2021-12-07 09:34:45
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\TIMER_Init.h
 */
#ifndef __TIMER_INIT_H
#define __TIMER_INIT_H
#include "stm32f10x.h"
#include "sys.h"

extern void TIMER_Init(int arr, int psc);
extern void TIM3_IRQHandler(void);
extern int i;
extern int hour, minuse, second;

#endif
