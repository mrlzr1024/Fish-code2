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

extern  void servo0(int mod,int U); //mod--哪位舵机,U--转的角度
extern void Semap1(int mod,int angle);//反
extern void Semap0(int mod,int angle);//正
extern void Timer0Interrupt(void) ;



#endif
