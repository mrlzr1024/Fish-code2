/*
 * @Author: your name
 * @Date: 2019-09-10 10:33:36
 * @LastEditTime: 2021-12-05 17:04:23
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USERc:\Users\梁芝瑞\Desktop\天堂制造\咸鱼先生的图书馆\【正点原子】STM32F103最小系统板资料\4，程序源码\1，标准例程-寄存器版本\实验3 串口实验\HARDWARE\LED\led.h
 */
#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板V3
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/1/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

//LED端口定义
#define LED0 PBout(5)	// DS0
#define LED1 PEout(5)	// DS1	

void LED_Init(void);	//初始化		 				    
#endif

















