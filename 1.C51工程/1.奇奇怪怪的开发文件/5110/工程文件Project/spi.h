#ifndef __SPI_H__
#define __SPI_H__
#include<reg52.h>
sbit LCD_CE=P1^1;
sbit LCD_DC=P1^2;
sbit SDIN=P1^3;
sbit SCLK=P1^4;
sbit LCD_RST=P1^0;
extern int font6x8[][6];
extern int blank[][6];
extern void LCD_write_byte(unsigned char dat, unsigned char command);//spi–¥ ˝æ›ªÚ√¸¡Ó
extern   void LCD_init(void);
extern void LCD_write_char(int h[][6]);
extern void LCD_set_XY(unsigned char X, unsigned char Y);
extern void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map, unsigned char Pix_x,unsigned char Pix_y);
extern void display(unsigned char x,unsigned char y,int h[][6]);
#endif
