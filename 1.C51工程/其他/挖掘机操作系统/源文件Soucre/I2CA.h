#ifndef _I2CA_H
#define _I2CA_H
#include<reg52.h>
#include <intrins.h>  
sbit scl=P3^6;                   //时钟输入线
sbit sda=P3^7;                   //数据输入/输出端
typedef  unsigned char  uchar;        
typedef  unsigned int   uint;        
	extern void delayus();//延时5us(大约)
	extern void init();
	extern void start();
	extern void stop();
	extern void ACK();
	extern void write_byte(uchar byte);
	extern uchar read_byte();//  读一个字节函数，有返回值
#endif