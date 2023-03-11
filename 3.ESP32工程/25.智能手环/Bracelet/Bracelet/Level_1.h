#ifndef __LEVEL_1_H
#define __LEVEL_1_H
#include "encode.h"

enum Level_1_Control
{
    Standard,
    second_Adjust,
    Minuse_Adjust,
    Hour_Adjust,
    Date_Adjust,
    Mounth_Adjust,
    Year_Adjust,
};

extern Level_1_Control level_1_Control;
extern void handleRotate(int8_t rotation);


#endif