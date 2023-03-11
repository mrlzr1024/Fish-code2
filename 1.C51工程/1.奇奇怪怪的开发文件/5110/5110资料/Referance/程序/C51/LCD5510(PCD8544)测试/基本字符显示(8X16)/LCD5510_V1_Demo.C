/*--------------------------------------------------------------*/
#include <AT89X52.H>
#include "Font_code.c"
#include "LCD5510_V1.H"


unsigned char code *str1 = {"Nokia 5510 Test, Haha^_^ I am so glad to see you agian! Do you think so?"};
unsigned char code *str2 = {"I Love You"};

/*--------------------------------------------------------------*/
//延时250000+1us 函数定义
void delay250ms(void)
{
    unsigned char i,j,k;
    for(i=251;i>0;i--)
    for(j=3;j>0;j--)
    for(k=164;k>0;k--);
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
	unsigned char i;
	unsigned char LCD_contrast = 0xc8;

	LCD5510_Init();

	while(*str1)
	{
		LCD_prints(0, 0, str1++); 
		delay250ms(); i++;
		LCD_clr_row(0);LCD_clr_row(1);
	}
	str1 -= i;
	LCD_prints(0, 0, str1);

	delay1s();
	for(i = 0; i < 10; i++) {LCD_printc(i, 1, str2[i]); delay250ms();}

	delay1s();
	LCD_prints(1, 2, "(*^_^*)");
	delay1s();
/*
	LCD_show_blank;		//空白测试
	delay1s();
	LCD_show_black;		//全黑检测坏点
	delay1s();
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_show_inverse;	//反色
	delay1s();
	LCD_show_normal;	//恢复正常
	delay1s();
	LCD_clr_scr();		//清屏
	delay1s();
	LCD_prints(1, 1, "Alexi2008");
	while(1)			//对比度软件调节
	{
		LCD_write_cmd(0x23);		//工作模式, 水平寻址, 扩展指令	

		for(i = 0; i < 10; i++) {LCD_contrast++; LCD_write_cmd(LCD_contrast); delay250ms();}
		for(i = 0; i < 20; i++) {LCD_contrast--; LCD_write_cmd(LCD_contrast); delay250ms();}
		for(i = 0; i < 10; i++) {LCD_contrast++; LCD_write_cmd(LCD_contrast); delay250ms();}
	}
*/
}

