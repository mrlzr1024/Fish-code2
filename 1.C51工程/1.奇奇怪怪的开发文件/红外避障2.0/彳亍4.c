#include <reg52.h>

//下面的是连接l298n模块的引脚与单片机引脚相连
sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit IN3 = P1^2;
sbit IN4 = P1^3;

//红外避障模块
sbit out1 = P2^0;
sbit out2 = P1^6;


/*函数声明*/
void go();			//前进
void back();		//后退
void left();		//向左
void right();		//向右
void stop();		//停止


void main()
{
	
	while(1)
	{
		if(out2 == 0)											//检测到右边有障碍物时，向左移动
		{
			left();
		}
		else if(out1 == 0)								//检测到左边边有障碍物时，向右移动
		{
			right();
		}
		else if(out1 == 1 && out2 == 1)		//检测到都没有有障碍物时，向前移动
		{
			go();
		}
	}
}

//前进
void go()
{
	IN1=1; 
	IN2=0; 
	IN3=1; 
	IN4=0;
}

//后退
void back()
{
	IN1=0; 
	IN2=1; 
	IN3=0; 
	IN4=1;
}

//向左
void left()
{
	IN1=0; 
	IN2=0; 
	IN3=0; 
	IN4=1;
}

//向右
void right()
{
	IN1=1; 
	IN2=1; 
	IN3=1; 
	IN4=0;
}

//停止
void stop()
{
	IN1=0; 
	IN2=0; 
	IN3=0; 
	IN4=0;
}

