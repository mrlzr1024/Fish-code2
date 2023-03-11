#include "TuringServo.h"
#include "Servo.h"
//#include "engine.h"
/*void delay3(void)   //误差 0us
//{
//    unsigned char a,b;
//    for(b=173;b>0;b--)
//        for(a=143;a>0;a--);
//}
*/
/***************************************************
 * 函数名称：moves1
 * 入口参数：//int mod1// int angle1//int mode1/------||-------/mod1--4逆时针 5--顺时针 angle--转的角度 mode--哪位舵机
 * 输出：当前设定的角度
 * 功能：驱动舵机
* 备注：步进=50*1us
 * *************************************************/
int moves1(int mod1, int angle1,int mode1 ){//mod1--4逆时针 5--顺时针 angle--转的角度 mode--哪位舵机
    int i = 0;
    switch (mod1)
    {
    case 4:
        angle1+=Step;
        if (angle1 > 2000) {angle1 = 2000;}
//            move(mode1, angle1);//
					servo0(mode1, angle1);
//					delay3();
        break;
    case 5:
        angle1-=Step;//尝试集：80,50
        if (angle1 < 0){angle1 = 0;}
//            move(mode1, angle1);//
					servo0(mode1, angle1);//
//					delay3();
        break;
    default:
        break;
    }
   // }
	return  angle1;
}
/***************************************************
 * 函数名称：moves2
 * 入口参数：//int from// int to//int mode1/------||-------/from--当前角度；to--目标角度；mode--哪位舵机
 * 输出：无
 * 功能：比较当前姿态(from)与目标姿态(to)并减速运动 即：有记忆地输出到舵机(简化板moves1() )
* 备注：无
 * *************************************************/
void moves2(int from ,int to ,int mode2){
	int w=0;
	int i=0;
	if (from>to){ for(w=from;w>=to;w-=Step){for(i=0;i<7;i++){servo0(mode2,w);}}}
	else if (from<to){ for(w=from;w<=to;w+=Step){for(i=0;i<7;i++){servo0(mode2,w);}}}
}



