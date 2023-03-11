/*
 * @Author: your name
 * @Date: 2021-11-17 07:38:08
 * @LastEditTime: 2021-11-17 08:22:32
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \机械臂\engine.c
 */
#include <REG52.h>
#include "engine.h"
static int T;
/***************************************************
 * 函数名称：delay100us
 * 入口参数：倍数 k
 * 输出：无
 * 功能：延时100*k us
 * 备注：无
 * *************************************************/
void delay100us(int k){ //延时k*100us
  k = k - 2;
  T = k;
  TMOD = 0x02;
  EA = 1;
  ET0 = 1;
  TH0 = 157; //100us要计92.16次 164
  TL0 = 0;
  TR0 = 1;
  while (T > 0)
    ;
  TR0 = 0;
}
/***************************************************
 * 函数名称：move
 * 入口参数：舵机第mod个 角度angle(0~20)
 * 输出：无
 * 功能：模拟pwm信号控制四个舵机
 * 备注：无
 * *************************************************/
void move(int mod, int angle) //180度舵机控制程序
{
  int pwm = 0;
  pwm = 5 + angle;
  switch (mod)
  {
  case 0:
    M0 = 1;
    delay100us(pwm);
    M0 = 0;
    delay100us(202 - pwm);
    break;
  case 1:
    a1 = 1;
    delay100us(pwm);
    a1 = 0;
    delay100us(202 - pwm);
    break;
  case 2:
    a2 = 1;
    delay100us(pwm);
    a2 = 0;
    delay100us(202 - pwm);
    break;
  case 3:
    a3 = 1;
    delay100us(pwm);
    a3 = 0;
    delay100us(202 - pwm);
    break;
  default:
    break;
  }
}
//  void main(void){
//    int i=0;
//    M0=0;
//    while(i<=3){
//      move(15);
//
//      i++;
//      }
//      i=0;
//    while(i<=3){
//      i++;
//      delay();
//    }
//      i=0;
//    while(i<=3){
//
//    move(5);
//    i++;
//      }
//    while(1)
//      ;
//    }
void time0(void) interrupt 1
{
  T--;
}
