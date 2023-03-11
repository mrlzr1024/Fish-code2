#ifndef __ENCODE_H
#define __ENCODE_H

#include <Versatile_RotaryEncoder.h>
#include "main.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"

// Set here your encoder reading pins (Ex.: EC11 with breakout board)
#define clk 15 // (A3)
#define dt 2   // (A4)
#define sw 0   // (A5)

enum mode
{
    Clock,
    Step,
    Heart_Rate,
    Gradienter, //水平仪
    TEmperature,
    DATE,
    WLAN,    //联网
    Network, //构建网页
    Advance, //天气预报
};

extern mode Mode_1;

extern int Rotation[3];
extern int level;

extern Versatile_RotaryEncoder *versatile_encoder;

extern void Encode_init();
extern void handleRotate(int8_t rotation);
extern void handlePressRotate(int8_t rotation);
extern void handleHeldRotate(int8_t rotation);
extern void handlePress();
extern void handlePressRelease();
extern void handleLongPress();
extern void handleLongPressRelease();
extern void handlePressRotateRelease();
extern void handleHeldRotateRelease();

#endif