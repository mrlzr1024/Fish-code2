/*---------------------------------------------------------------
         IIC总线所需的通用函数
----------------------------------------------------------------*/
#include"I2CA.h"
#include<reg52.h>
/*---------------------------------------------------------------
                 微妙级别延时函数 大于4.7us
----------------------------------------------------------------*/
void delayus()//延时5us(大约)
{
		_nop_();          //在intrins.h文件里
		_nop_();
		_nop_();
		_nop_();
		_nop_();
}
/*---------------------------------------------------------------
                 IIC总线初始化函数 
----------------------------------------------------------------*/
void init()
{
    sda=1;                //sda scl使用前总是被拉高
    delayus();
    scl=1;
    delayus();
}
/*---------------------------------------------------------------
                 IIC总线启动信号函数
----------------------------------------------------------------*/
void start()
{
    sda=1;
    delayus();
    scl=1;                        //scl拉高时 sda突然来个低电平 就启动了IIC总线
    delayus();
    sda=0;
    delayus();
    scl=0;
    delayus();
}
/*---------------------------------------------------------------
                 IIC总线停止信号函数
----------------------------------------------------------------*/
void stop()
{
    sda=0;
    delayus();
    scl=1;                         //scl拉高时 sda突然来个高电平 就停止了IIC总线
    delayus();
    sda=1;                   
    delayus();
}
/*---------------------------------------------------------------
                 IIC总线应答信号函数
----------------------------------------------------------------*/
void ACK()
{
    uchar i;
    scl=1;
    delayus();
    while((sda=1)&&(i<255))         
			i++;                                        
    scl=0;                                  
    delayus();
}
/*---------------------------------------------------------------
                 写一个字节,无返回值，需输入一个字节值
----------------------------------------------------------------*/
void write_byte(uchar byte)
{
    uchar i,temp;
    temp=byte;
    for(i=0;i<8;i++)
    {
        temp=temp<<1;  
        scl=0;                  
				delayus();
				sda=CY;                 
				delayus();
				scl=1;           
				delayus();
    }
    scl=0;                  
    delayus();
    sda=1;                 
    delayus();
}
/*---------------------------------------------------------------
                 读一个字节函数，有返回值
----------------------------------------------------------------*/
uchar read_byte()//uchar 范围=（0~256）=2^8
{
		uchar i,j,k;
		scl=0;
		delayus();
		sda=1;
		delayus();
		for(i=0;i<8;i++)        
		{
			delayus();
			scl=1;
			delayus();
			if(sda==1)
			{
					j=1;
			}
			else j=0;
			k=(k<< 1)|j;  
			scl=0;            
		}
		delayus();
		return k;
}