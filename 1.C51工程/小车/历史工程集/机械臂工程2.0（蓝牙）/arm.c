/*
 * @Author: your name
 * @Date: 2021-11-17 07:31:44
 * @LastEditTime: 2021-11-21 09:08:10
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \机械臂\arm.c
 */
#include <reg52.h>
#include "engine.h"
//#include "key.h"
#include "oled.h"
#include "Uart.h"
unsigned char code di_09[][8]={//0~9
{0x00,0x3E,0x41,0x41,0x41,0x41,0x3E,0x00}//"0",0
/* (8 X 8 , 新宋体 ) */
,{0x00,0x00,0x00,0x00,0x41,0x7F,0x00,0x00}//"1",1
/* (8 X 8 , 新宋体 ) */
,{0x00,0x00,0x42,0x61,0x51,0x49,0x49,0x46}//"2",2
/* (8 X 8 , 新宋体 ) */
,{0x00,0x00,0x22,0x41,0x41,0x49,0x4F,0x32}//"3",3
/* (8 X 8 , 新宋体 ) */
,{0x00,0x00,0x18,0x14,0x12,0x51,0x7F,0x00}//"4",4
/* (8 X 8 , 新宋体 ) */
,{0x00,0x2E,0x49,0x45,0x45,0x49,0x39,0x00}//"5",5
/* (8 X 8 , 新宋体 ) */
,{0x00,0x3E,0x49,0x45,0x45,0x49,0x38,0x00}//"6",6
/* (8 X 8 , 新宋体 ) */
,{0x00,0x03,0x01,0x71,0x09,0x07,0x01,0x00}//"7",7
/* (8 X 8 , 新宋体 ) */
,{0x00,0x36,0x4D,0x49,0x49,0x49,0x36,0x00}//"8",8
/* (8 X 8 , 新宋体 ) */
,{0x00,0x4E,0x49,0x51,0x51,0x29,0x1E,0x00}//"9",9
/* (8 X 8 , 新宋体 ) */
};
unsigned char code di_abcd[][8]={
{0x00,0x68,0x54,0x54,0x54,0x38,0x40,0x40}//"a",0
/* (8 X 8 , 新宋体 ) */

,{0x00,0x00,0x7F,0x48,0x44,0x44,0x44,0x38}//"b",1
/* (8 X 8 , 新宋体 ) */

,{0x00,0x00,0x38,0x44,0x44,0x44,0x48,0x28}//"c",2
/* (8 X 8 , 新宋体 ) */

,{0x00,0x00,0x38,0x44,0x44,0x44,0x44,0x7F}//"d",3
/* (8 X 8 , 新宋体 ) */
,{0x00,0x38,0x54,0x54,0x54,0x54,0x18,0x00}//"e",4
/* (8 X 8 , 新宋体 ) */

,{0x00,0x00,0x04,0x44,0x7E,0x45,0x05,0x01}//"f",5
/* (8 X 8 , 新宋体 ) */
};
unsigned char code show1[] ={//“凸”
        0x78, 0x4E, 0x42, 0x42, 0x42, 0x42, 0x4E, 0x78
};
void delay(void) {//延时1s
    unsigned char a, b, c;
    for (c = 167; c > 0; c--)
        for (b = 171; b > 0; b--)
            for (a = 16; a > 0; a--)
                ;
}
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
            move(mode1, angle1);
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
            move(mode1, angle1);
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
void main(void)
{
	int mode=0;//哪位舵机
	int key=0;//传回来的数据
	int a=0;//舵机角度
	int tmp=0;
	int i=0,j=0;
	int  m[2][40];//储存舵机状态
	oledInit();
	display(0,0,show1);//就绪标志
	while (1){
			/*=============================================================================*/
//			key=key4x4();
				key=BluetoothGet();
				display(0,6,di_09[key]);
			/*key=0~3*/if(key>=0&&key<=3){mode=key;}//识别哪一位舵机【第(mode)位】
			/*=============================================================================*/
			/*储存*/if(key==7){
			m[0][j]=mode;
			m[1][j]=a;
			display(i,0,di_09[m[0][j]]);
			display(i,1,di_09[m[1][j]]);
			i++;
			j++;
			if(i>=8){i=0;}
			if(j>=8){j=0;}
			} 
			/*=============================================================================*/
				/*输出*/if(key==6){
					j--;
					while(j>=0){
									mode=m[0][j];
									a=m[1][j];
						for(tmp=0;tmp<7;tmp++){
									moves1(4,a,mode);
						}
									display(0,2,di_09[mode]);
									display(0,3,di_09[a]);
									display(j,5,di_09[a]);
							    display(j,4,di_09[mode]);
										j--;
										delay();
					}
					j=0;
					i=0;
				}
			/*=============================================================================*/

			/*key=4~5*/if(key==4){a=moves1(4,a,mode);}//正转
			else if(key==5){a=moves1(5,a,mode);}//反转
			/*=============================================================================*/
			display(0,2,di_09[mode]);
			display(0,3,di_09[a]);
		}			
}
//for(;j>0;j--){moves1(4,m[1][j],m[0][j]);}
/*第一次记忆实验（成功）
						while (1){
		mod=key4x4();
		if(mod==0){a=moves1(4,a,0);}
		if(mod!=b){P3=0xfe;}
		else {P3=0xfc;}
		b=mod;
		if (mod==1){a=moves1(5,a,0);}
		if (mod==2){delay();moves1(4,a,0);}
							}*/
/*阻滞性运动(识别)
    mod = key();
        if (mod == 1)
        {
            angle ++;
            if (angle >= 20)
            {
                angle = 0;
            }
        }
        else if (mod == 2)
        {
            angle --;
            if (angle <= 0)
            {
                angle = 0;
            }
        }
        //while(i<3){
        move(0, angle);
        //i++;
        //}
        //i=0;
        //delay();*/
/*非阻滞性运动（识别）
while(key_continue()==1){
        move(0, angle);
        angle ++;
        if(angle>=20){angle=20;}
        }
        while(key_continue()==2){
        move(0, angle);
        angle --;
        if(angle<=0){angle=0;}*/