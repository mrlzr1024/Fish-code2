/*
 * @Author: your name
 * @Date: 2022-04-14 13:49:47
 * @LastEditTime: 2022-04-14 14:00:52
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \小车\test.c
 */
#include<reg51.h>
#include <TuringServo.h>
#include "Servo.h"
sbit M0=P1^0;
void main(void){
  servo_init_0();
  moves1(4,90,1)

  }
