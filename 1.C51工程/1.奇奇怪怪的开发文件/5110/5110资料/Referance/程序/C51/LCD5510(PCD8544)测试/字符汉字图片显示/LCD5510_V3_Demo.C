/*--------------------------------------------------------------*/
#include <AT89X52.H>
#include "LCD5510_V3.H"

unsigned char code *str1 = {"Nokia 5510 Test, Haha ^_^ I am so glad to see you agian! Do you think so?"};
unsigned char code *str2 = {"I Love You AVR"};
unsigned char code pic[] = 
{//84*48
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x20,0x20,0xC0,0x70,0x20,0x30,0x20,0x40,0x80,0xC0,0x40,0x20,0x30,0x20,
0x20,0x20,0x50,0xC0,0x80,0x20,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0xC0,0x40,0x40,0x80,0xC0,0x40,0xA0,0x60,0xB0,0xB0,0xD0,0xF0,0x70,0xF0,
0xB0,0x60,0xA0,0x60,0x00,0x00,0x00,0xC0,0x60,0x30,0x18,0x0C,0x04,0x06,0x82,0x46,
0x02,0xE2,0x02,0x02,0x02,0x06,0x06,0x8F,0x8C,0x8F,0x9F,0xB0,0x30,0x74,0x63,0xC0,
0x8E,0x0F,0x0E,0x00,0x00,0x00,0x80,0x80,0xE3,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0xB8,0x44,0xE2,0x43,0x03,0x06,0xF8,0x45,0xF2,0x1C,0xC7,
0xE2,0x02,0x03,0x02,0x0D,0x3A,0xC5,0x5A,0x00,0x00,0x3F,0xF7,0xC0,0x00,0x00,0x00,
0x3C,0xC2,0x3D,0xC2,0x15,0x40,0x00,0x00,0x00,0x00,0x02,0x03,0x05,0x05,0x07,0x01,
0x06,0x01,0x00,0x00,0x00,0x01,0x03,0x03,0x05,0x0B,0x21,0x9E,0x21,0xDF,0x2C,0xF8,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xC0,0x20,0xD0,0xF8,0x90,0x9C,0x97,0x92,0xF4,0xF4,0x0E,0xA2,0x55,
0xAA,0x03,0x5E,0xA8,0x11,0x50,0xB0,0x58,0xAC,0x07,0x79,0x86,0x00,0x00,0x00,0x01,
0x03,0x07,0x0E,0xAC,0xFC,0x59,0xBA,0xF1,0xB6,0x35,0x32,0x34,0xE8,0x30,0x60,0x20,
0x20,0x20,0x30,0xE0,0x30,0x10,0x10,0x18,0x88,0x6C,0x1E,0x03,0x00,0x00,0x01,0xA2,
0x14,0xEA,0x15,0xEA,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFD,0xA2,0x5D,0xA2,0xFF,0x95,0x6B,0x95,0x69,
0x86,0x58,0xA2,0x55,0xAA,0x40,0xB5,0x4A,0xA0,0x55,0xAA,0xD4,0xA9,0x56,0xA9,0x56,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0E,0x0D,0x3A,0x35,0x6B,0xD6,0xEC,
0x9D,0xEE,0x18,0xE8,0x18,0xE0,0x1C,0xE7,0x14,0xEA,0x96,0xE1,0xD1,0xA8,0xE0,0xE8,
0xF4,0x2A,0x39,0x1A,0x1D,0x0E,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x06,
0x3F,0x7D,0xFE,0xF9,0xBE,0x39,0x1E,0xBD,0xFC,0x7F,0x3C,0x77,0xCE,0x77,0x8B,0x75,
0x8A,0x75,0x8A,0xF5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x03,0x0B,0x0F,0x03,0x0D,0x03,0x0C,0x03,0x0C,
0x03,0x0C,0x03,0x0D,0x03,0x0F,0x0E,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x08,
0x0F,0x05,0x0A,0x05,0x0A,0x05,0x0A,0x07,//d:\我的文档\桌面\2009-08-05_100029.bmp0
};

unsigned char code pic1[] = {//72*14
0x1C,0x08,0xFE,0x08,0x08,0xFA,0xAF,0xFA,0x08,0x00,0x00,0x00,0x80,0x7C,0x80,0x00,
0x00,0x00,0x94,0x56,0x3C,0xD4,0x00,0x38,0x28,0x38,0x00,0x00,0xF4,0x94,0x94,0xDC,
0x00,0x00,0x00,0x00,0xC1,0xFF,0xFC,0x8D,0x3D,0x78,0x00,0x00,0x00,0x00,0x01,0x01,
0x09,0x05,0x1D,0x3D,0x7D,0x7F,0x1B,0x0B,0x83,0xFF,0x7F,0x3F,0x8F,0x87,0x03,0x83,
0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0x00,0x00,0x28,0x28,0x28,0x28,0x28,0x29,0x28,0x2B,
0x28,0x28,0x29,0x29,0x28,0x28,0x28,0x29,0x28,0x28,0x28,0x28,0x20,0x04,0x0A,0x12,
0x24,0x12,0x0A,0x24,0x20,0x28,0x28,0x00,0x10,0x18,0x3C,0x3F,0x3F,0x3F,0x3F,0x3F,
0x38,0x20,0x00,0x03,0x30,0x30,0x20,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,
0x21,0x30,0x38,0x3F,0x3C,0x3C,0x3F,0x3F,0x3F,0x3F,0x3F,0x0F,0x21,0x28,0x28,0x28};
//F:\学习\单片机\单片机工具\取字模软件\BMP图片\收藏\6.bmp0

unsigned char code pic2[] = {//72*28
0xFF,0x4D,0x43,0x41,0x41,0x41,0x41,0x41,0x01,0x01,0x03,0x05,0x0B,0x17,0x1F,0x1D,
0x13,0x15,0xBB,0xF5,0xEB,0xD5,0xAB,0xF5,0xEB,0xD5,0xAB,0xD5,0xAB,0xD5,0xAB,0x55,
0x2B,0x77,0xBF,0x00,0x14,0x14,0x94,0xFC,0x92,0x50,0xFE,0x10,0x92,0x54,0x10,0x00,
0x00,0xE0,0x00,0xF8,0x00,0x02,0x1C,0x00,0x00,0x60,0x80,0x00,0x00,0x70,0xF0,0xF0,
0xE0,0xC0,0xE0,0xF0,0xF0,0x70,0x00,0x00,0xFF,0x46,0x0F,0xDF,0xAF,0x47,0xAF,0x1E,
0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x0E,0x0C,0xEE,0x46,0x86,0x56,
0xBE,0x5C,0x38,0x00,0x06,0x09,0xC8,0x18,0xEC,0x55,0xAA,0x00,0x01,0x89,0x88,0x8F,
0x84,0x84,0x82,0x83,0x84,0x88,0x0E,0x00,0x01,0x80,0x80,0x8F,0x88,0x88,0x88,0x88,
0x8F,0x80,0x01,0x00,0x00,0x00,0x00,0x81,0x03,0x07,0x83,0x01,0x00,0x00,0x00,0x00,
0xFF,0x55,0xBE,0xE0,0x81,0x01,0x01,0x01,0x00,0x00,0x06,0x08,0x40,0x40,0x40,0x40,
0x40,0x00,0x00,0x00,0x01,0x03,0x03,0x03,0x02,0x81,0x40,0x20,0x10,0xFC,0xA9,0x58,
0xAB,0x55,0xAA,0x00,0x00,0xFF,0x02,0xBA,0xAA,0xAA,0xFE,0xAA,0xAA,0xBB,0x80,0x00,
0x08,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x04,0xFE,0x89,
0x44,0x33,0x02,0xFA,0x02,0x32,0xC6,0x00,0x0F,0x05,0x0A,0x0F,0x0A,0x05,0x0A,0x0C,
0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x04,0x04,0x02,0x02,
0x01,0x00,0x00,0x00,0x00,0x0F,0x0A,0x05,0x0A,0x05,0x0A,0x00,0x03,0x00,0x00,0x03,
0x00,0x02,0x03,0x02,0x00,0x02,0x03,0x00,0x00,0x00,0x00,0x02,0x02,0x03,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x02,0x02,0x03,0x00,0x00,0x00,0x00};
//F:\学习\单片机\单片机工具\取字模软件\BMP图片\收藏\1040699005093204[1].bmp0


/*--------------------------------------------------------------*/
//延时50000+0us 函数定义
const unsigned char code pic3[206] = {0x00,0x80,0x80,0xC0,0xE0,0xF0,0xB8,0xB8,0xDC,0x2C,0xDE,0x2E,0xFE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0x7E,0x5C,0x1C,0x38,0x38,0xF0,0xE0,0xE0,0xC0,
0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xC3,0x63,0x79,0x3B,0x3F,0x1F,0x1F,
0x1F,0x0F,0x2F,0xFE,0x3F,0x66,0x07,0x47,0x6F,0x67,0x3F,0x2F,0x3F,0x2F,0x3F,0x18,
0x18,0x38,0x3E,0x3E,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF8,0x78,0x38,
0x00,0x00,0x00,0x00,0x40,0xA0,0x18,0x08,0x00,0x0C,0x08,0x0F,0x3F,0xE0,0x00,0x02,
0x0F,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAA,
0xFF,0xCF,0x9F,0x9F,0xDF,0xEF,0x7F,0x00,0x00,0x00,0x00,0x00,0x01,0x16,0xFC,0x88,
0x10,0x10,0x18,0x08,0x06,0x03,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xFA,0x7F,0x7F,0x7F,0x3F,0x1F,0x07,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x04,0x0C,0x08,0x10,0x30,0x30,0x30,
0x38,0x2C,0x6E,0x23,0x60,0x20,0x20,0x30,0x10,0x18,0x98,0xDC,0x70,0x7A,0x3B,0x3F,
0x18,0xB8,0x58,0xB8,0x58,0xB0,0x70,0xE0};

void delay50ms(void)
{
    unsigned char i,j,k;
    for(i=165;i>0;i--)
    for(j=60;j>0;j--)
    for(k=1;k>0;k--);
}

//延时200000+0us 函数定义
void delay200ms(void)
{
    unsigned char i,j,k;
    for(i=201;i>0;i--)
    for(j=32;j>0;j--)
    for(k=14;k>0;k--);
}


//延时1000000+1us 函数定义
void delay1s(void)
{
    unsigned char i,j,k;
    for(i=167;i>0;i--)
    for(j=171;j>0;j--)
    for(k=16;k>0;k--);
}


/*--------------------------------------------------------------*/
//主函数
void main(void)
{
	unsigned char i, j, k;
	unsigned char LCD_contrast = 0xb8;	//此值对比度合适

	LCD5510_Init();

LCD_prints(0, 3, ">>>Welcome<<<");
delay1s();	delay1s();
while(*str1)
{		LCD_prints(0, 0, str1++); 
	delay200ms(); i++;
	LCD_clr_row(0);	}
str1 -= i;
	LCD_printsl(0, 0, str1);
delay1s();
	
LCD_clr_scr();		//清屏
	delay1s();
	LCD_picture(pic);
	delay1s();	delay1s(); 
	
	LCD_clr_scr();		//清屏
	delay1s();
	LCD_pos_picture(0, 0, 40, 40, pic3);	
	delay1s();	
	LCD_pos_picture(0, 2, 72, 28, pic2);
	delay1s(); delay1s();
	LCD_clr_scr();		//清屏
	LCD_showsh(0, 0, "我心★永恒");
	delay1s();
	LCD_showsh(0, 1, "永恒★我心");
	delay1s();
	LCD_showsh(0, 2, "永恒之心★");
	delay1s(); delay1s();
	
	
	
	LCD_clr_scr();		//清屏
	for(i = 0; i < 14; i++) {LCD_printc(i, 2, str2[i]); delay200ms();}
	LCD_printn(2, 3, 13140, 5);
	delay1s();
	LCD_prints(0, 4, ">--(*^_^*)--<");
	delay1s();


	LCD_prints(0, 0, "Blank Test ");
	delay1s();
	LCD_show_blank;		//空白测试
	delay1s();
	LCD_prints(0, 0, "Normal Test");
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_prints(0, 0, "Black Test ");
	delay1s();
	LCD_show_black;		//全黑检测坏点
	delay1s();
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_prints(0, 0, "Inverse Test");
	LCD_show_inverse;	//反色
	delay1s();
	LCD_prints(0, 0, "Normal again");
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_clr_scr();		//清屏
	delay1s();
	
	
	i = 0; j = 0; k =0;
	LCD_prints(0, 5, "ASCII Code:"); 
	while(k++ < 100)	//ASCII字符测试
	{ 
		LCD_printc(i, j, k + 32); 
		delay50ms(); 
		i++; if(i == 14) {i = 0; j++;}
		if(j == 5) j = 0;
		LCD_printn(11, 5, k + 32, 3); 		
	}
	delay1s();
	
	
	LCD_clr_scr();			//清屏
	LCD_prints(2, 0, "Nokia 5510");
	LCD_prints(2, 2, "Alexi2008");
	LCD_prints(0, 4, "LCD_Contrast:");
//	while(1)				//对比度软件调节
//	{
//		for(i = 0; i < 10; i++) 
//		{
//			LCD_contrast++; 
//			LCD_write_cmd(0x21);//工作模式, 水平寻址, 扩展指令
//			LCD_write_cmd(LCD_contrast);
//			LCD_write_cmd(0x20);//工作模式, 水平寻址, 常规指令
//			LCD_printc(13, 4, 129);
//			LCD_printn(5, 5, LCD_contrast, 3); 
//			delay200ms();
//		}
//		for(i = 0; i < 20; i++) 
//		{
//			LCD_contrast--; 
//			LCD_write_cmd(0x21);//工作模式, 水平寻址, 扩展指令
//			LCD_write_cmd(LCD_contrast);
//			LCD_write_cmd(0x20);//工作模式, 水平寻址, 常规指令 
//			LCD_printc(13, 4, 130);
//			LCD_printn(5, 5, LCD_contrast, 3); 
//			delay200ms();
//		}
//		for(i = 0; i < 10; i++) 
//		{
//			LCD_contrast++; 
//			LCD_write_cmd(0x21);//工作模式, 水平寻址, 扩展指令
//			LCD_write_cmd(LCD_contrast);
//			LCD_write_cmd(0x20);//工作模式, 水平寻址, 常规指令
//			LCD_printc(13, 4, 129);
//			LCD_printn(5, 5, LCD_contrast, 3); 
//			delay200ms();
//		}
//	}
	while(1)
		;
}

