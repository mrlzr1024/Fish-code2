/*--------------------------------------------------------------*/
//File:	LCD5510_V1.H
//Date:	2009/8/4
//Time: 9:16
//Note: Nokia 5510 LCD液晶显示
//每8位显示数据是低位在上, 高位在下
//测试硬件
//单片机:  STC89C52RC
//模式:    12T
//晶振:	   12MHz


/*--------------------------------------------------------------*/
//防止重复引用
#ifndef	__LCD5510_V1_H__
#define __LCD5510_V1_H__


/*--------------------------------------------------------------*/
//指令宏定义
#define X_Col_Addr     0x80		//定位到第0列指令(列起始地址)(0 - 83)
#define Y_Page_Addr    0x40		//定位到第0页指令(页起始地址)(0 - 5)


/*--------------------------------------------------------------*/
//功能宏定义
//液晶复位
#define LCD_reset_hard	LCD_RST = 0; LCD_RST = 1	//硬件复位
#define LCD_reset_soft	LCD_reset_5510()			//软件复位
//液晶显示控制(不影响DDRAM)
#define LCD_show_blank		LCD_write_cmd(0x08)		//显示空白
#define LCD_show_normal		LCD_write_cmd(0x0c)		//正常显示
#define LCD_show_black		LCD_write_cmd(0x09)		//显示全黑
#define LCD_show_inverse 	LCD_write_cmd(0x0d)		//反色显示
//便于理解
#define LCD_write_cmd(cmd)	LCD_write_byte(cmd, 0)	//写入指令
#define LCD_write_dat(dat)	LCD_write_byte(dat, 1)	//写入数据


/*--------------------------------------------------------------*/
//数据接口定义
//sbit LCD_CLK = P2^0;     //串行时钟			//上升沿写入数据
//sbit LCD_DIN = P2^1;     //串行数据输入		//先高后低
//sbit LCD_DC  = P2^2;     //数据指令控制端	//高电平数据，低电平指令
//sbit LCD_CS  = P2^3;     //片选使能			//低电平有效
//sbit LCD_RST = P2^4;     //LCD复位端		//低电平复位

/*
sbit LCD_CLK = P0^0;
sbit LCD_DIN = P0^1;     
sbit LCD_DC  = P0^2;     
sbit LCD_CS  = P0^3;     
sbit LCD_RST = P0^4;
*/

/*--------------------------------------------------------------*/
//函数声明(私有)
void LCD_write_byte(unsigned char wbyte, unsigned char dat_cmd);//写入字节
void LCD_pos_char(unsigned char x, unsigned char y);			//液晶定位(8*8)
void LCD_reset_5510(void);										//复位LCD5510


/*--------------------------------------------------------------*/
//函数声明(公有)
/*--------------------------------------------------------------*/
//清屏参数(清DDRAM)
void LCD_clr_scr(void);


/*--------------------------------------------------------------*/
//液晶字节定位(1*1)
//液晶规划:
//x: 0 - 83
//y: 0 - 5
void LCD_pos_byte(unsigned char x, unsigned char y);


/*--------------------------------------------------------------*/
//液晶字符输出(8*16字体)
//x: 0 - 9
//y: 0 - 2
void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat);


/*--------------------------------------------------------------*/
//液晶字符串输出(8*16字体)
//x: 0 - 9
//y: 0 - 2
void LCD_prints(unsigned char x, unsigned char y, unsigned char code *s_dat);


/*--------------------------------------------------------------*/
//初始化LCD5510
void LCD5510_Init(void);				


/*--------------------------------------------------------------*/
//包含文件
#include "LCD5510_V1.C"


/*--------------------------------------------------------------*/
#endif





 
