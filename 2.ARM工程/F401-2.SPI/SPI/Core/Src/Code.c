/*
 * @Author: your name
 * @Date: 2022-01-16 17:21:08
 * @LastEditTime: 2022-01-18 16:26:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \SPI\Core\Src\Code.c
 */
#include <Code.h>
#include "oled_driver.h"
unsigned char buffer[128][8]; //点缓冲区
unsigned char code0_9[][16] = //目标图像
    {
        {0x00, 0xC0, 0x20, 0x10, 0x10, 0x10, 0x20, 0xC0, 0x00, 0x07, 0x08, 0x10, 0x10, 0x10, 0x08, 0x07}, /*"0",0*/
        /* (8 X 16 , Century )*/
        {0x00, 0x00, 0x20, 0x20, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x00}, /*"1",1*/
        /* (8 X 16 , Century )*/
        {0x00, 0xE0, 0xB0, 0x10, 0x10, 0x10, 0x10, 0xE0, 0x00, 0x10, 0x18, 0x14, 0x12, 0x12, 0x11, 0x18}, /*"2",2*/
        /* (8 X 16 , Century )*/
        {0x00, 0x20, 0x10, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00, 0x0C, 0x14, 0x10, 0x10, 0x10, 0x08, 0x0F}, /*"3",3*/
        /* (8 X 16 , Century )*/
        {0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0xF0, 0x00, 0x00, 0x06, 0x05, 0x04, 0x14, 0x14, 0x1F, 0x14}, /*"4",4*/
        /* (8 X 16 , Century )*/
        {0x00, 0x00, 0xF0, 0x90, 0x90, 0x90, 0x90, 0x10, 0x00, 0x0D, 0x14, 0x10, 0x10, 0x10, 0x09, 0x0F}, /*"5",5*/
        /* (8 X 16 , Century )*/
        {0x00, 0xC0, 0x20, 0xB0, 0x90, 0x90, 0x90, 0x20, 0x00, 0x07, 0x09, 0x10, 0x10, 0x10, 0x09, 0x07}, /*"6",6*/
        /* (8 X 16 , Century )*/
        {0x00, 0x60, 0x10, 0x10, 0x10, 0xD0, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x01, 0x00, 0x00}, /*"7",7*/
        /* (8 X 16 , Century )*/
        {0x00, 0x60, 0x90, 0x90, 0x10, 0x10, 0x90, 0x60, 0x00, 0x0E, 0x1A, 0x11, 0x11, 0x11, 0x1B, 0x0E}, /*"8",8*/
        /* (8 X 16 , Century )*/
        {0x00, 0xC0, 0x20, 0x10, 0x10, 0x10, 0x20, 0xC0, 0x00, 0x19, 0x13, 0x12, 0x12, 0x12, 0x09, 0x07},
        /*"9",9*/ /* (8 X 16 , Century )*/
};
unsigned char Sbmp[1024]; //图像缓冲区
/**
  *@功能：使大小小于128x64的图像适应128x64的屏幕
  *@参数：bmmp:目标图像
        ·length:目标图像长度
        ·wide:目标图像宽度
        ·odds:起始点（x坐标）
  *@输出：无
**/
void Resize(unsigned char *bmmp, int length, int wide, int odds)
{
    int x = 0;
    int tmp = 0;
    // while (tmp < 1024)
    // {
    //     Sbmp[tmp] = 0x00;
    //     tmp++;
    // }
    tmp = odds;
    while (x < length * wide / 8)
    {
        while (tmp % 128 < length + odds)
        {
            Sbmp[tmp++] |= bmmp[x++];
        }
        // OLED_FILL(Sbmp);
        tmp += 128 - length;
    }
}
/**
 *@功能：画像素点
 *@参数：x,y坐标
 *@输出：无
 *@PS:x=[0,128];y=[0,63]
 **/
void SetPixel(unsigned char x, unsigned char y)
{
    /*处理*/
    buffer[x][y / 8] |= 0x01 << (y % 8);

    /*输出*/
    OLED_WR_Byte(0xb0 + y / 8, OLED_CMD);  // page0-page1
    OLED_WR_Byte(0x00 + x % 16, OLED_CMD); // low column start address
    OLED_WR_Byte(0x10 + x / 16, OLED_CMD); //  hight column start address
    OLED_WR_Byte(buffer[x][y / 8], OLED_DATA);
}
/**
 *@功能：清除像素点
 *@参数：x,y坐标
 *@输出：无
 *@PS:x=[0,128];y=[0,63]
 **/
void CleanPixel(unsigned char x, unsigned char y)
{
    /*处理*/
    buffer[x][y / 8] &= ~(0x01 << (y % 8));

    /*输出*/
    OLED_WR_Byte(0xb0 + y / 8, OLED_CMD);  // page0-page1
    OLED_WR_Byte(0x00 + x % 16, OLED_CMD); // low column start address
    OLED_WR_Byte(0x10 + x / 16, OLED_CMD); //  hight column start address
    OLED_WR_Byte(buffer[x][y / 8], OLED_DATA);
}
/**
 *@功能：清空屏幕和点缓冲区及图像缓冲区
 *@参数：无
 *@输出：无
 *@PS:无
 **/
void Clean(void)
{
    int tmp = 0, x = 0, y = 0;
    while (tmp < 1024)
    {
        Sbmp[tmp] = 0x00;
        tmp++;
    }
    while (y <= 8)
    {
        buffer[x][y] = 0x00;
        x++;
        if (x >= 128)
        {
            x = 0;
            y++;
        }
    }
    OLED_FILL(Sbmp);
}