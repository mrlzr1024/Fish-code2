#ifndef _PCA9685_H
#define _PCA9685_H
	#include"I2CA.h"
	#include <intrins.h>  
	#include <stdio.h>
	#include <math.h>
	#define PCA9685_adrr 0x80//  1+A5+A4+A3+A2+A1+A0+w/r 
	#define PCA9685_SUBADR1 0x2
	#define PCA9685_SUBADR2 0x3
	#define PCA9685_SUBADR3 0x4


	#define PCA9685_MODE1 0x00
	#define PCA9685_PRESCALE 0xFE


	#define LED0_ON_L 0x06
	#define LED0_ON_H 0x07
	#define LED0_OFF_L 0x08
	#define LED0_OFF_H 0x09


	#define ALLLED_ON_L 0xFA
	#define ALLLED_ON_H 0xFB
	#define ALLLED_OFF_L 0xFC
	#define ALLLED_OFF_H 0xFD

	extern void delayms(uint z);
	extern void PCA9685_write(uchar address,uchar date);
	extern uchar PCA9685_read(uchar address);
	extern void begin(void);
	extern void setPWMFreq(float freq);
	extern void servo_control(uchar num, uchar angle);
	extern void reset(void);

#endif