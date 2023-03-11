/*
 * @Author: your name
 * @Date: 2021-11-23 10:09:58
 * @LastEditTime: 2021-11-23 10:50:24
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \undefinedc:\Users\梁芝瑞\Desktop\天堂制造\嵌入式学习笔记\MDK,keil5的模块0元购商店\oled显示\oled.h
 */
#ifndef __OLED_H__
#define __OLED_H__
#include <reg52.h>
#define high 1
#define low 0
/*************Pin Define***************/
sbit SCL = P0 ^ 0;
sbit SDA = P0 ^ 1;
extern void oledInit(void);
extern void display(unsigned char x, unsigned char y, unsigned char hok[][8],int num);
extern void fill_picture(unsigned char fill_Data);
/***********************Picture Code**************************/
//unsigned char code show1[] ={//“凸”
//        0x78, 0x4E, 0x42, 0x42, 0x42, 0x42, 0x4E, 0x78
//};
/***********************Picture Code**************************/
#endif
