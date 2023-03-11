#include "Arduino.h"

#ifndef JQ8900_cpp
    #define JQ8900_cpp


/******************IO定义**************************/
extern int IO_JQ8X00_BusyCheck;        //忙检测IO

/******************全局变量**************************/
extern int JQ8X00_BusyCheck;     //忙检测，0表示不做忙检测，1表做忙检测


typedef enum
{
    JQ8X00_USB                      = 0X00,                 /*UPANND*/
    JQ8X00_SD                       = 0x01,                 /*SD*/
    JQ8X00_FLASH                 = 0x02,                    /*FLASH*/
}JQ8X00_Symbol;      //系统盘符

typedef enum
{
    AppointTrack                    = 0x07,                 /*指定曲目播放*/
    SetCycleCount                   = 0x19,                 /*设置循环次数*/
    SetEQ                           = 0X1A,                 /*EQ设置*/
    SelectTrackNoPlay               = 0x19,                 /*选曲不播放*/
    GoToDisksign                    = 0X0B,                 /*切换指定盘符*/
    SetVolume                       = 0x13,                 /*音量设置*/
    SetLoopMode                     = 0x18,                 /*设置循环模式*/
    SetChannel                      = 0x1D,                 /*设置通道*/
    AppointTimeBack                 = 0x22,                 /*指定时间快退*/
    AppointTimeFast                 = 0x23,                 /*指定时间快退*/
}UartCommandData;      //包含多个数据的指令,起始码-指令类型-数据长度-数据1-...-校验和

void  JQ8x00_Command_Data(UartCommandData Command, unsigned char DATA);
void JQ8x00_AppointPlay(JQ8X00_Symbol MODE, char *DATA);
void  JQ8x00_ZuHeBoFang(unsigned char *DATA, unsigned char Len);

#endif
