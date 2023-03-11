/*
 * @Author: your name
 * @Date: 2021-11-24 21:16:21
 * @LastEditTime: 2021-12-11 19:35:59
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \机械臂\TuringServo.h
 */
#ifndef  __TURINGSERVO_H__
#define __TURINGSERVO_H__
#define Step 45	//步进
#define Step1 50	//记忆步进
extern  int moves1(int mod1, int angle1,int mode1 );//mod1--4逆时针 5--顺时针 angle--转的角度 mode--哪位舵机
extern void moves2(int from ,int to ,int mode2);//from--当前角度；to--目标角度；mode--哪位舵机


#endif
