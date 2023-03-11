#ifndef __TIMER_H
#define __TIMER_H

#include "main.h"
#include "Level_3.h"
#include "Hear_Detect.h"
extern float getHeartRate;
extern uint8_t getSpO2;
extern int step;
extern float x, y, z;

extern void Timer0_init();
extern void Timer1_init();
extern void Save_info();
extern void Task(); //线程————探测加速度
extern void Task_2();//线程————联网

#endif