/*
 * @Author: your name
 * @Date: 2022-03-26 10:59:38
 * @LastEditTime: 2022-03-31 17:39:55
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\Car.h
 */
#ifndef  __CAR_H
#define  __CAR_H
#include "My_GPIO.H"
#include "sys.h"
#include "main.h"


extern void Init_Car(int pin_a, int pin_b, int pin_c, int pin_d);
extern void forward(int num,int Deviation);

extern void left(int num);
extern void right(int num);
extern void back(int num,int Deviation);
extern void stop(void);
#endif


