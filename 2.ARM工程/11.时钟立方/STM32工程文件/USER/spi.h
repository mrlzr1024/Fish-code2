/*
 * @Author: your name
 * @Date: 2021-12-06 17:33:20
 * @LastEditTime: 2021-12-06 17:49:21
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\spi.h
 */
#ifndef __SPI_H__
#define __SPI_H__
#include "stm32f10x.h"

#include "sys.h" 
#define SCLK PAout(1)  //SCLK=4;
#define SDIN PAout(2)  //SDIN=3;
#define LCD_DC PAout(3)  //DC=2;
#define LCD_CE PAout(4)  //CE=1;
#define LCD_RST PAout(5)  

//sbit LCD_CE=P1^1;
//sbit LCD_DC=P1^2;
//sbit SDIN=P1^3;
//sbit SCLK=P1^4;
//sbit LCD_RST=P1^0;
extern int font6x8[][6];
extern int blank[][6];
extern void LCD_write_byte(unsigned char dat, unsigned char command);//spi写数据或命令
extern   void LCD_init(void);
extern void LCD_write_char(int h[][6]);
extern void LCD_set_XY(unsigned char X, unsigned char Y);
extern void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map, unsigned char Pix_x,unsigned char Pix_y);
extern void display(unsigned char x,unsigned char y,int h[][6]);
#endif
