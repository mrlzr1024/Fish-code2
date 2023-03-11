/*
 * @Author: your name
 * @Date: 2021-12-05 20:17:05
 * @LastEditTime: 2021-12-15 07:14:21
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
#include "spi.h"
#include "CharCode.h"
#include "TIMER_Init.h"
#include "sys.h"
//#include "usart.h"
// #include "stdio.h"
 #include "USARTer.h"
#include "RED.h"
void clock(int sx, int sy, int hour, int minuse, int second)
{
    /*hour*************************************/
    LCD_draw_bmp_pixel(sx, sy, MAP[hour / 10], 8, 16);
    sx += 8;
    LCD_draw_bmp_pixel(sx, sy, MAP[hour % 10], 8, 16);
    sx += 8;
    /*':'***************************************/
    LCD_draw_bmp_pixel(sx, sy, MAP[10], 8, 16);
    sx += 8;
    /*minuse************************************/
    LCD_draw_bmp_pixel(sx, sy, MAP[minuse / 10], 8, 16);
    sx += 8;
    LCD_draw_bmp_pixel(sx, sy, MAP[minuse % 10], 8, 16);
    sx += 8;
    /*':'***************************************/
    LCD_draw_bmp_pixel(sx, sy, MAP[10], 8, 16);
    sx += 8;
    /*second************************************/
    LCD_draw_bmp_pixel(sx, sy, MAP[second / 10], 8, 16);
    sx += 8;
    LCD_draw_bmp_pixel(sx, sy, MAP[second % 10], 8, 16);
    sx = 0;
    if (minuse == 0 && second < 2)
    {
        PAout(0) = 1;
    }
    else if (minuse == 0 && second == 2)
    {
        PAout(0) = 0;
    }
}
void SumInit(void)
{
    Stm32_Clock_Init(9); //系统时钟：8*9=72
    delay_init(72);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    InitGPIO(1, 50, GPIOA);
    InitGPIO(2, 50, GPIOA);
    InitGPIO(3, 50, GPIOA);
    InitGPIO(4, 50, GPIOA);
    InitGPIO(5, 50, GPIOA);
    InitGPIO(0, 50, GPIOA); //背光板正极
    /*初始化串口*********************************/
    // GPIOInit(GPIOB, GPIO_Mode_Out_PP, GPIO_Pin_12, RCC_APB2Periph_GPIOB, GPIO_Speed_50MHz); //电源1
    // GPIOInit(GPIOB, GPIO_Mode_Out_PP, GPIO_Pin_14, RCC_APB2Periph_GPIOB, GPIO_Speed_50MHz); //电源1
    /*电源**************************************/
    LCD_init();
    TIMER_Init(9999, 7199);
    EXTIInit();//<<<======
    USART_Init1();
    /*初始化函数**********************************/
    PAout(0) = 0;
}
int main(void)
{
    int sx = 0, sy = 0; //时钟显示的起始地址
    int xx, yy;         //附加模块显示的起始地址
    int tmp = 0;
    hour = 12;
    minuse = 0;
    SumInit(); //总初始化
    yy = 3;
    for (xx = 0; xx <= 72; xx += 8) //附加模块显示
    {
        LCD_draw_bmp_pixel(xx, yy, MAP1[tmp], 8, 16);
        tmp++;
    }
    while (1)
    {
        /*蓝牙*******************************************/
					 if ((a & 0xf0) == 0xa0) //控制小时
					 {
							 hour++;
							 a = 0x00;
							 if (hour >= 24)
							 {
									 hour = 0;
							 }
					 }
					 else if ((a & 0xf0) == 0xb0) //控制分钟
					 {
							 minuse++;
							 a = 0x00;
							 if (minuse >= 60)
							 {
									 minuse = 0;
							 }
					 }
					 else if ((a & 0xf0) == 0xc0) //控制秒
					 {
							 second = 0;
							 i = 0;
							 a = 0x00;
					 }
        // /*红外********************************************/
        /*时间********************************************/
        if ((IrValue[2]) == 0x40) //控制小时
        {
            hour--;
        }
        if ((IrValue[2]) == 0x43) //控制小时
        {
            hour++;
        }
        if ((IrValue[2]) == 0x15) //控制分钟
        {
            minuse--;
        }
        if ((IrValue[2]) == 0x09) //控制分钟
        {
            minuse++;
        }
        if ((IrValue[2]) == 0x07) //控制秒
        {
            second = 0;
            i = 0;
        }
        if (minuse < 0)
        {
            minuse = 59;
        }
        if (minuse > 59)
        {
            minuse = 0;
        }
        if (hour < 0)
        {
            hour = 23;
        }
        if (hour > 23)
        {
            hour = 0;
        }
        /*外设********************************************/
        if ((IrValue[2]) == 0x45) //控制背景灯
        {
            PAout(0) = !PAout(0);
        }
        IrValue[2] = 0x00;
        clock(sx, sy, hour, minuse, second);
    }
}
