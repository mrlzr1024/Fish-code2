/*--------------------------------------------------------------*/
//File:	LCD5510_V3.H
//Date:	2009/8/5
//Time: 18:16
//Note: Nokia 5510 LCD液晶显示
//每8位显示数据是低位在上, 高位在下
//测试硬件
//单片机:  ATMEGA8
//晶振:	   1MHz(内部)


/*--------------------------------------------------------------*/
//防止重复引用
#ifndef	__LCD5510_V3_H__
#define __LCD5510_V3_H__


/*--------------------------------------------------------------*/
//数据接口定义
//输出
#define LCD_CLK		P_OUT(C, 0)	//串行时钟			//上升沿写入数据
#define LCD_DIN		P_OUT(C, 1)	//串行数据输入		//先高后低
#define LCD_DC		P_OUT(C, 2)	//数据指令控制端	//高电平数据，低电平指令
#define LCD_CS		P_OUT(C, 3)	//片选使能			//低电平有效
#define LCD_RST		P_OUT(C, 4)	//LCD复位端			//低电平复位
//方向
#define LCD_CLK_DIR	DDR(C, 0)	//串行时钟			//上升沿写入数据
#define LCD_DIN_DIR	DDR(C, 1)	//串行数据输入		//先高后低
#define LCD_DC_DIR	DDR(C, 2)	//数据指令控制端	//高电平数据，低电平指令
#define LCD_CS_DIR	DDR(C, 3)	//片选使能			//低电平有效
#define LCD_RST_DIR	DDR(C, 4)	//LCD复位端			//低电平复位

#define DIR_IN		0			//输入
#define DIR_OUT		1			//输出


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
//函数声明(私有)
void LCD_write_byte(unsigned char wbyte, unsigned char dat_cmd);//写入字节
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
//显示清行
//num:	0 - 5
void LCD_clr_row(unsigned char num);


/*--------------------------------------------------------------*/
//液晶字符输出(6*8字体)
//x: 0 - 13
//y: 0 - 5
void LCD_printc(unsigned char x, unsigned char y, unsigned char c_dat);


/*--------------------------------------------------------------*/
//液晶字符串输出(6*8字体)(ROM)
//x: 0 - 13
//y: 0 - 5
void LCD_prints(unsigned char x, unsigned char y, const unsigned char *s_dat);


/*--------------------------------------------------------------*/
//液晶字符串输出(6*8字体)(RAM)
//x: 0 - 13
//y: 0 - 5
void LCD_prints_ram(unsigned char x, unsigned char y, unsigned char *s_dat);


/*--------------------------------------------------------------*/
//液晶字符串输出,自动换行(6*8字体)(ROM)
//x: 0 - 13
//y: 0 - 5
void LCD_printsl(unsigned char x, unsigned char y, const unsigned char *s_dat);


/*--------------------------------------------------------------*/
//液晶汉字输出(16*16字体)(ROM)
//查表显示输出
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//x: 0 - 4
//y: 0 - 2
void LCD_showch(unsigned char x, unsigned char y, const unsigned char *dat);


/*--------------------------------------------------------------*/
//液晶汉字词组输出(16*16字体)(ROM)
//查表显示输出
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//x: 0 - 4
//y: 0 - 2
//一行最多5个
void LCD_showsh(unsigned char x, unsigned char y, const unsigned char *dat);


/*--------------------------------------------------------------*/
//显示84X48图片(ROM)
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
void LCD_picture(const unsigned char *img_dat);


/*--------------------------------------------------------------*/
//定位显示指定大小图片(ROM)
//取码规则:	低位在前, 列行扫描, 阴码(1-亮, 0-灭)
//pag:	0 - 5			页坐标
//col:  0 - 83			列坐标
//x:	0 - (83-col)	图片宽
//y:	0 - (47-pag*8)	图片高
void LCD_pos_picture(unsigned char col, unsigned char pag, unsigned char x, unsigned char y, const unsigned char *img_dat);


/*--------------------------------------------------------------*/ 
//定位输出数字
//x: 0 - 13
//y: 0 - 5
//num: 0 - 65535	要显示的数字
//num_bit: 0 - 5	数字的位数
void LCD_printn(unsigned char x, unsigned char y, unsigned int num, unsigned char num_bit);


/*--------------------------------------------------------------*/
//初始化LCD5510
void LCD5510_Init(void);				


/*--------------------------------------------------------------*/
//包含文件
#include "Font_ASCII_code.C"	//ASCII字体库
#include "Font_GBK_code.c"		//汉字库
#include "LCD5510_V3.C"			//函数库


/*--------------------------------------------------------------*/
#endif





 
