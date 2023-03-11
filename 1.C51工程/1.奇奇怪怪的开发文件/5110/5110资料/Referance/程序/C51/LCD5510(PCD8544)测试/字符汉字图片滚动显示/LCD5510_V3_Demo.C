/*--------------------------------------------------------------*/
#include <AT89X52.H>
#include "LCD5510_V3.H"
#include "IMG_code.c"


unsigned char code *str1 = {"Nokia 5510 Test, Haha^_^ I am so glad to see you agian! Do you think so?"};
unsigned char code *str2 = {"I Love You AVR"};


/*--------------------------------------------------------------*/
//延时50000+0us 函数定义
void delay50ms(void)
{
    unsigned char i,j,k;
    for(i=167;i>0;i--)
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
	unsigned int i, j, k;
	unsigned char LCD_contrast = 0xc8;	//此值对比度合适
	unsigned char *ptr;

	LCD5510_Init();

	ptr = str1;
	i = 0;
	while(i++ < 641-84)
	{
		LCD_prints(0, 5, ptr++);
		LCD_roll_picture(0, 0, 40, &img1[i*5]);// 40/8 = 5
		if(!(i%72)) ptr -= 72;
		LCD_clr_row(5);
	}

	i = 0;
	while(*str1)
	{
		LCD_prints(0, 0, str1++); 
		delay200ms(); i++;
		LCD_clr_row(0);
	}
	str1 -= i;
	LCD_printsl(0, 0, str1);
	delay1s();
	
	LCD_clr_scr();		//清屏
	delay1s();
	LCD_picture(pic);
	delay1s();	delay1s(); 
	
	LCD_clr_scr();		//清屏
	delay1s();
	LCD_pos_picture(0, 0, 72, 14, pic1);	
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
	while(1)				//对比度软件调节
	{
		for(i = 0; i < 10; i++) 
		{
			LCD_contrast++; 
			LCD_write_cmd(0x21);//工作模式, 水平寻址, 扩展指令
			LCD_write_cmd(LCD_contrast);
			LCD_write_cmd(0x20);//工作模式, 水平寻址, 常规指令
			LCD_printc(13, 4, 129);
			LCD_printn(5, 5, LCD_contrast, 3); 
			delay200ms();
		}
		for(i = 0; i < 20; i++) 
		{
			LCD_contrast--; 
			LCD_write_cmd(0x21);//工作模式, 水平寻址, 扩展指令
			LCD_write_cmd(LCD_contrast);
			LCD_write_cmd(0x20);//工作模式, 水平寻址, 常规指令 
			LCD_printc(13, 4, 130);
			LCD_printn(5, 5, LCD_contrast, 3); 
			delay200ms();
		}
		for(i = 0; i < 10; i++) 
		{
			LCD_contrast++; 
			LCD_write_cmd(0x21);//工作模式, 水平寻址, 扩展指令
			LCD_write_cmd(LCD_contrast);
			LCD_write_cmd(0x20);//工作模式, 水平寻址, 常规指令
			LCD_printc(13, 4, 129);
			LCD_printn(5, 5, LCD_contrast, 3); 
			delay200ms();
		}
	}
}

