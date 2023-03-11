/*
 * @Descripttion: Project's name
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-15 15:50:55
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-18 17:02:01
 */
#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"
#include "main.h"
int PID_Calc_Left(int NextPoint,int Setpoint);
int PID_Calc_Right(int NextPoint,int Setpoint);
void showPID(void);
#endif

