/*
 * @Author: your name
 * @Date: 2022-03-26 10:59:38
 * @LastEditTime: 2022-03-26 11:58:32
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\Car.h
 */
#ifndef  __CAR_H
#define  __CAR_H
#include "My_GPIO.H"
#include "sys.h"

extern void Init_Car(int pin_a, int pin_b, int pin_c, int pin_d);
extern void forward(void);

extern void left(void);
extern void right(void);
extern void back(void);

#endif


