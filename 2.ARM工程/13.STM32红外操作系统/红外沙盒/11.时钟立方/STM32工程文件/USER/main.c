/*
 * @Author: LZR
 * @Date: 2021-12-05 20:17:05
 * @LastEditTime: 2021-12-23 14:37:11
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
#include "USARTer.h"
#include "RED.h"
#define HIGH 0
#define LOW 1
#define respons 6 //回应的位GPIOAx
/*发送逻辑位*/
void out(int x)
{
    PBout(0) = LOW;
    delay_us(560);
    PBout(0) = HIGH;
    if (x == 1)
    {
        delay_us(1680);
    }
    else if (x == 0)
    {
        delay_us(560);
    }
}
/*发送8Bit数据*/
void send(unsigned char DATA)
{
    int i, j;
    unsigned char signal[4] = {0x00, 0xff, 0xf8, 0xff};
    signal[2] = DATA; //数据位
    signal[1] = ~signal[0];
    signal[3] = ~signal[2];
    PBout(0) = LOW;
    delay_ms(9);
    PBout(0) = HIGH;
    delay_us(4500);
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if ((signal[i] & (0x01 << j)) > 0)
            {
                out(1);
            }
            else if ((signal[i] & (0x01 << j)) == 0)
            {
                out(0);
            }
        }
    }
}
/*调节并显示*/
void clock(int sx, int sy, int hour, int minuse, int second1, int mode) //响应点======================================
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
    LCD_draw_bmp_pixel(sx, sy, MAP[second1 / 10], 8, 16);
    sx += 8;
    LCD_draw_bmp_pixel(sx, sy, MAP[second1 % 10], 8, 16);
    sx = 0;
    /*整点报时***********************************/
    if (mode == 0) //响应点======================================================================================
    {
        if (minuse == 0 && second1 < 2)
        {
            PAout(respons) = 1;
        }
        else if (minuse == 0 && second1 == 2)
        {
            PAout(respons) = 0;
        }
    }
}
/*总初始化*/
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
    InitGPIO(respons, 50, GPIOA); //背光板正极,回应位
                                  /*初始化待机系统*********************************/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    InitGPIO(0, 50, GPIOB);
    /*电源**************************************/
    LCD_init();
    TIMER_Init(9999, 7199);
    EXTIInit(); //<<<======
    USART_Init1();
    /*初始化函数**********************************/
    PAout(respons) = 0;
    LCD_draw_bmp_pixel(0, 0, CLKmode[2], 84, 48);
    delay_ms(1000);
    LCD_clear();
}
/*自定义界面*/
void chara(int xx, int yy)
{ //附加模块显示的起始地址
    int tmp = 0;
    for (xx = 0; xx <= 72; xx += 8) //附加模块显示
    {
        LCD_draw_bmp_pixel(xx, yy, MAP1[tmp], 8, 16);
        tmp++;
    }
}
int main(void)
{
    int sx = 0, sy = 0; //时钟显示的起始地址
    int mode = 0, smode = 0;//主模式，进入模式
    int Chour = 0, Cminuse = 0;//闹钟小时，分钟值
    int Shour = 0, Sminuse = 0, Ssecond = 0, sem = 0; // sem控制是否开启倒数计时 Shour,Sminuse,Ssecond倒数计时小时，分钟，秒值  
    int swidh = 0;//倒数计时进入开关
    int g = 0; //从主时钟线截取变化
    int tmp = 0;
    hour = 12;
    minuse = 0;
    SumInit(); //总初始化
    chara(0, 4);
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
        /*模式********************************************/
        switch (mode)
        {
        case 0:
            clock(sx, sy, hour, minuse, second, 0);
            chara(0, 4);
            break;
        case 1: //闹钟
        case 2: //倒数计时
            LCD_draw_bmp_pixel(0, 0, CLKmode[mode - 1], 84, 48);
            smode = mode;
            break;
        default:
            break;
        }
        switch (smode)
        {
        case 1:
            if (swidh == 1)
            {
                clock(sx, sy, Chour, Cminuse, 0, 1);
            }
            break;
        case 2:
            if (swidh == 1)
            {
                clock(sx, sy, Shour, Sminuse, Ssecond, 2);
            }
            break;
        default:
            break;
        }
        /*闹钟控制*****************************************/
        if (hour == Chour && minuse == Cminuse && second <= 2) //响应点===<<<=
        {                                                      //亮2秒
            PAout(respons) = 1;                                //作为响应
        }
        if (hour == Chour && minuse == Cminuse && second == 3)
        {
            PAout(respons) = 0;
        }
        /*倒数计时*****************************************/
        if (IrValue[2] == 0x07 && mode == -2)
        {
            if (sem == 0)
            {
                sem = 1;
            }
            else if (sem == 1)
            {
                sem = 0;
                Ssecond = 0;
                Sminuse = 0;
                Shour = 0;
            }
            IrValue[2] = 0x00;
        }
        if (sem == 1) //响应点===<<<=
        {
            g = i;
            while (g == i)
                ;
            Ssecond--;
            if (Ssecond < 0)
            {
                Ssecond = 59;
                Sminuse--;
            }
            if (Sminuse < 0)
            {
                Sminuse = 59;
                Shour--;
            }
            if (Shour == 0 && Sminuse == 0 && Ssecond == 0) //响应点=====================================================
            {
                sem = 0;
                clock(sx, sy, Shour, Sminuse, Ssecond, 2);
                PAout(respons) = 1; //作为响应
                EXTI->IMR &= ~(EXTI_Line12);
                for (tmp = 0; tmp < 15; tmp++)
                {
                    send(0xdd);
                    delay_ms(10);
                }
                delay_ms(5);
                PAout(respons) = 0;
                EXTI->IMR |= EXTI_Line12;
            }
        }
        /*红外控制(主)**************************************/
        if (IrValue[2] == 0x00)
        {
            continue;
        }
        switch (IrValue[2]) //响应点===<<<=
        {
        /*减少小时值******************************************/
        case 0x40: //减少小时值
            if (mode == 0)
                hour--;
            else if (mode == -1)
            {
                Chour--;
            }
            else if (mode == -2)
            {
                Sminuse--;
            }
            break;
        /*增加小时值******************************************/
        case 0x43: //增加小时值
            if (mode == 0)
                hour++;
            else if (mode == -1)
            {
                Chour++;
            }
            else if (mode == -2)
            {
                Sminuse++;
            }
            break;
        /*减少分钟值******************************************/
        case 0x15: //减少分钟值
            if (mode == 0)
                minuse--;
            else if (mode == -1)
            {
                Cminuse--;
            }
            else if (mode == -2)
            {
                Ssecond--;
            }
            break;
        /*倒数计时复位***************************************/
        case 0x16: //倒数计时复位
            Ssecond = 0;
            Sminuse = 0;
            Shour = 0;
            sem = 0;
            break;
        /*增加分钟值*****************************************/
        case 0x09: //增加分钟值
            if (mode == 0)
                minuse++;
            else if (mode == -1)
            {
                Cminuse++;
            }
            else if (mode == -2)
            {
                Ssecond++;
            }
            break;
        /*秒复位*******************************************/
        case 0x07: //秒复位
            if (mode == 0)
            {
                second = 0;
                i = 0;
            }
            break;
        /*外设********************************************/
        case 0x45:                            //响应点===<<<=
            PAout(respons) = !PAout(respons); //控制背景灯翻转
            break;
        /*设置模式******************************************/
        case 0x46:
        { //设置模式
            if (mode != -1)
            {
                mode++;
            }
            LCD_clear();
            PAout(respons) = 0; //控制背景灯
            if (mode < 0 || mode >= 3)
            {
                swidh = 0;
                mode = 0;
            }
        }
        break;
        /*休眠模式******************************************/
        case 0x47:
            LCD_clear();
            LCD_draw_bmp_pixel(0, 0, CLKmode[2], 84, 48);
            PAout(respons) = 0;
            while (IrValue[2] == 0x47)
                ;
            LCD_clear();
            break;
        /*确认********************************************/
        case 0x44: //
            if (mode != 0 && swidh == 0)
            {
                swidh = 1;
            }
            else if (swidh == 1)
            {
                swidh = 0;
            }
            LCD_clear();
            mode = -mode; //模式
            break;
        default:
            break;
        }
        /*时间界限*****************************************/
        if (minuse < 0)
        {
            minuse = 59;
        }
        else if (minuse > 59)
        {
            minuse = 0;
        }
        if (hour < 0)
        {
            hour = 23;
        }
        else if (hour > 23)
        {
            hour = 0;
        }
        if (Cminuse < 0)
        {
            Cminuse = 59;
        }
        else if (Cminuse > 59)
        {
            Cminuse = 0;
        }
        if (Chour < 0)
        {
            Chour = 23;
        }
        else if (Chour > 23)
        {
            Chour = 0;
        }
        /*倒数计时界限**************************************/
        if (Ssecond > 59)
        {
            Ssecond = 0;
            Sminuse++;
        }
        else if (Ssecond < 0)
        {
            Ssecond = 59;
            Sminuse--;
        }
        if (Sminuse < 0)
        {
            Sminuse = 59;
            Shour--;
        }
        else if (Sminuse > 59)
        {
            Sminuse = 0;
            Shour++;
        }
        if (Shour < 0)
        {
            Shour = 23;
        }
        else if (Shour > 23)
        {
            Shour = 0;
        }
        IrValue[2] = 0x00;
    };
}
