/*
 * @Author: your name
 * @Date: 2022-04-14 13:51:58
 * @LastEditTime: 2022-04-14 18:46:51
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \小车\Servo.h
 */
/*
	这是用来代替engine.c的函数
*/
#ifndef  __SERVO_H__
#define __SERVO_H__
#include <reg51.h>
sbit M0 = P2 ^ 0;
sbit a1 = P2 ^ 1;
sbit a2 = P2 ^ 2;
sbit a3 = P2 ^ 3;
extern void servo_init_0(void);//初始化定时器
extern  void servo0(int mod,int U); //mod--哪位舵机,U--转的角度
extern void Timer0Interrupt(void) ;



#endif
