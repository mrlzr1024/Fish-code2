#ifndef __I2CB_H_
#define __I2CB_H_

#include<reg52.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

//--定义使用的IO口--//
sbit I2C_SCL = P3^4;
sbit I2C_SDA = P3^5;

//--声明全局变量--//
void I2C_Delay10us();
void I2C_Start();
void I2C_Stop();
uchar I2C_SendByte(uchar dat, uchar ack);
uchar I2C_ReadByte();

#endif
