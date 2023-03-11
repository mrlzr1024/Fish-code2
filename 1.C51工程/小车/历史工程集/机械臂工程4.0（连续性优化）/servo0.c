#include "Servo.h"
#include "intrins.h"
int T = 0;
/*void delay20(void)   //延时至少20ms(消抖)
//{
//      unsigned char a,b,c;
//    for(c=2;c>0;c--)
//        for(b=95;b>0;b--)
//            for(a=209;a>0;a--);
//    _nop_();  //if Keil,require use intrins.h
//}
*/

/***************************************************
 * 函数名称：servo0
 * 入口参数：int mod,int U     //    mod--哪位舵机,U--转的角度；U=0~2000
 * 输出：无
 * 功能：驱动舵机
* 备注：角度=0~2000
 * *************************************************/
void servo0(int mod,int U) {//mod--哪位舵机,U--转的角度
	T =500+ U;
	TMOD = 0x01;
	TH0 = 0;
	TL0 = 0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
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
/***************************************************Semap0正转
* 函数名称：Semap0正转（映射函数）（0~2000）—>(0~20)
 * 入口参数：int mod,int U     //    mod--哪位舵机,U--转的角度；U=0~20
 * 输出：无
 * 功能：与TuringServo.h的moves1函数对接，驱动舵机
* 备注：角度=0~20
 * *************************************************
//void Semap0(int mod,int angle){//正
//		int i=0;
//	if(angle>=20){
//	for (i=(angle-1)*100;i<=angle*100;i+=100){
//		servo0(mod,i);
//			delay20();
//	}
//}
//}
*/
/***************************************************Semap1反转
* 函数名称：Semap1反转（映射函数）（0~2000）—>(0~20)
 * 入口参数：int mod,int U     //    mod--哪位舵机,U--转的角度；U=0~20
 * 输出：无
 * 功能：与TuringServo.h的moves1函数对接，驱动舵机
* 备注：角度=0~20
 * *************************************************
//void Semap1(int mod,int angle){//反
//		int i=0;
//		if(angle<=20){
//	for (i=(angle+1)*100;i>=angle*100;i-=100){
//		servo0(mod,i);
//				delay20();
//	}
//}
//}
*/
/*void main(void)
{
	int i = 0;
	int j = 0;
	while (1)
	{
		{
			move(0,i);
		}
		i+=20;
		if (i > 2000)
		{
			i = 0;
		}
	}
}
*/
void Timer0Interrupt(void) interrupt 1{
	TR0 = 0;
}
