/*
 * @Descripttion: Project's name
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-13 19:50:43
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-13 20:21:39
 */
#ifndef __MY_CAR
#define __MY_CAR

#include "stm32f10x.h"
//硬件链接说明
//电机控制pwm,用到了timer3的ch3和ch4，即 PB0-PB1连接电机驱动的使能端PWMA（左电机）和PWMB（右电机）
//电机正反控制：INA1和INA2控制 一路（左电机）
//	  				 INB1和INB2控制 一路（右电机）
//             PWMA ---- PB0
//             PWMB ---- PB1
//             INA2 ---- PB12
//             INA1 ---- PB13
//             INB1 ---- PB14
//             INB2 ---- PB15
//             PB0控制PWMA--left motor，PB1控制PWMB--right

extern void Car_PWM_Init(void);
extern void PWM_Init(u32 arr, int psc);
extern void PWM_Out(u16 moto_l, u16 moto_r);
extern void GPIO_Config(void);



#endif
