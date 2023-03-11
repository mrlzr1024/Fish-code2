#ifndef __CAR_H
#define __CAR_H

// #include "main.h"
#include <Arduino.h>

#define Position_Kp 1
#define Position_Ki 1
#define Position_KD 1
//#define support_l 50
#define support_r 0


extern float left, right;
extern int direction_r,direction_l;
extern void Action(bool a, bool b, bool c, bool d);
extern void Car_init();
extern int pid_ctrl(int Encoder, int Target);
extern void encode_init();
extern float left_speed();
extern float right_speed();
extern void pwm_write(int pwm, int pwm2);
extern void output(float pidd,int direction,int dist);
extern bool Accident(float angle);



#endif