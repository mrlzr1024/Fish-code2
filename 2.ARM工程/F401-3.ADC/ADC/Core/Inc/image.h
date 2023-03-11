/*
 * @Author: your name
 * @Date: 2022-01-17 11:54:29
 * @LastEditTime: 2022-01-17 22:02:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \SPI\Core\Inc\image.h
 */
#ifndef __IMAGE_H
#define __IMAGE_H
#include <main.h>
#define WRITE 1
#define CLEAN 0
/**
 *@功能：画像素圆
 *@参数：a,b(圆心坐标)，wide(边框厚度)，R(半径)
 *@输出：无
 *@PS:勿过界
 **/
extern void Draw_circle(unsigned char a, unsigned char b, unsigned char R, unsigned char wide);
/**
 *@功能：画像素半径
 *@参数：a,b(圆心坐标)，race(比率)，R(半径)
 *@输出：无
 *@PS:勿过界
 **/
extern void Draw_Point(unsigned char a, unsigned char b, unsigned char R, unsigned char race);
/**
 *@功能：画像素线
 *@参数：upperX,upperY(上坐标),bottomX，bottomY(下坐标)
 *@输出：无
 *@PS:勿过界
 **/
extern void Draw_Line(unsigned char upperX,
                      unsigned char upperY,
                      unsigned char bottomX,
                      unsigned char bottomY,
                      int mode);
/**
 *@功能：清除上面的像素线
 *@参数：无
 *@输出：无
 *@PS:勿过界
 **/
extern void Clean_line(void);
extern unsigned int count;
#endif