#include "TuringServo.h"
//#include "Servo.h"
#include "engine.h"
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
* 备注：步进为9度
 * *************************************************/
int moves1(int mod1, int angle1,int mode1 ){//mod1--4逆时针 5--顺时针 angle--转的角度 mode--哪位舵机
    int i = 0;
    switch (mod1)
    {
    case 4:
        angle1++;
        if (angle1 >= 20)
        {
            angle1 = 20;
        }
        while (i < 3)
        {
            move(mode1, angle1);//
//					Semap0(mode1, angle1);
//					delay3();
            i++;
        }
        i = 0;
        //delay();
        break;
    case 5:
        angle1--;
        if (angle1 <= 0)
        {
            angle1 = 0;
        }
        while (i < 3)
        {
            move(mode1, angle1);//
//					Semap1(mode1, angle1);//
//					delay3();
            i++;
        }
        i = 0;
        //delay();
        break;
    default:
        break;
    }
   // }
	return  angle1;
}
