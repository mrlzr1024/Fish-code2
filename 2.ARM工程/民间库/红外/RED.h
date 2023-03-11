/*
 * @Author: your name
 * @Date: 2021-12-14 07:59:02
 * @LastEditTime: 2021-12-14 08:26:42
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\RED.h
 */
#ifndef __RED_H
#define __RED_H
#include "GPIOBInit.h"
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
/***********************************************************
函数名称：EXTIInit
函数功能：初始化串口GPIOB_13
入口参数：无
出口参数：无
备 注：
***********************************************************/
extern void EXTIInit(void);
/***********************************************************
函数名称：EXTI0_IRQHandler
函数功能：捕捉红外信号
入口参数：无
出口参数：无
备 注：
***********************************************************/
extern void EXTI0_IRQHandler(void);
extern uint8_t IrValue[6]; //[0]=地址码；[1]=地址反码；[2]=控制码；[3]=控制反码
#endif       

//






































