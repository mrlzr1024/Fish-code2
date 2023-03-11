/*
 * @Author: your name
 * @Date: 2021-11-17 07:46:58
 * @LastEditTime: 2021-11-17 08:24:37
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \机械臂\engine.h
 */
#ifndef __ENGINE_H__
#define __ENGINE_H__
#include <REG52.h>
sbit M0 = P2 ^ 0;
sbit a1 = P2 ^ 1;
sbit a2 = P2 ^ 2;
sbit a3 = P2 ^ 3;
extern void move(int mod, int angle); //180度舵机控制程序

#endif