#ifndef _I2CA_H
#define _I2CA_H
#include<reg52.h>
#include <intrins.h>  
sbit scl=P3^6;                   //ʱ��������
sbit sda=P3^7;                   //��������/�����
typedef  unsigned char  uchar;        
typedef  unsigned int   uint;        
	extern void delayus();//��ʱ5us(��Լ)
	extern void init();
	extern void start();
	extern void stop();
	extern void ACK();
	extern void write_byte(uchar byte);
	extern uchar read_byte();//  ��һ���ֽں������з���ֵ
#endif