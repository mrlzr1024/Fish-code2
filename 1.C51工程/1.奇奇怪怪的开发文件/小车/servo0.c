/*
 * @Author: your name
 * @Date: 2022-04-14 13:51:58
 * @LastEditTime: 2022-04-14 18:46:42
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \小车\servo0.c
 */
#include "Servo.h"
#include "intrins.h"
int T = 0;
/***************************************************
 * 函数名称：servo_init
 * 入口参数：无
 * 输出：无
 * 功能：初始化定时器
* 备注：无
 * *************************************************/
void servo_init_0(void){
	T =500+ U;
	TMOD |= 0x01;
	TH0 = 0;
	TL0 = 0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	PX0=0;////////////<+===================
}
/***************************************************
 * 函数名称：servo0
 * 入口参数：int mod,int U     //    mod--哪位舵机,U--转的角度；U=0~2000
 * 输出：无
 * 功能：驱动舵机
* 备注：角度=0~2000
 * *************************************************/
void servo0(int mod,int U) {//mod--哪位舵机,U--转的角度

	while (TL0 + TH0 * 256 < T)
	{
		if(mod==0){M0 = 1;}
		else if(mod==1){a1 = 1;}
		else if(mod==2){a2 = 1;}
		else if(mod==3){a3 = 1;}
	}
	while (TL0 + TH0 * 256 >= T && TL0 + TH0 * 256 <= 20000)
	{
		if(mod==0){M0 = 0;}
		else if(mod==1){a1 = 0;}
		else if(mod==2){a2 = 0;}
		else if(mod==3){a3 = 0;}
	}
	TR0 = 0;
}

void Timer0Interrupt(void) interrupt 1{
	TR0 = 0;
}
