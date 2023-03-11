#ifndef  __TURINGSERVO_H__
#define __TURINGSERVO_H__
#define Step 50	//步进
extern  int moves1(int mod1, int angle1,int mode1 );//mod1--4逆时针 5--顺时针 angle--转的角度 mode--哪位舵机
extern void moves2(int from ,int to ,int mode2);//from--当前角度；to--目标角度；mode--哪位舵机


#endif
