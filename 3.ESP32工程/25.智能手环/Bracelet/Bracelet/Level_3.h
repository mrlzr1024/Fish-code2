#ifndef __LEVEL_3_H
#define __LEVEL_3_H
#include "encode.h"
#include "Hear_Detect.h"
#include "Temp.hpp"
#include "ADXL346.h"
#include <My_Network.h>

extern bool Clock_switch;
extern bool Hear_Detect_switch;
extern float x_1, y_1, z_1, temper;
extern float HeartRate;
extern uint8_t SpO2;

extern void handlePress();
extern void Clock_total();
extern void heart_detect(bool Switch);
extern void Gradienter_detect();
extern void Date_detect();
extern void Step_detect();

#endif