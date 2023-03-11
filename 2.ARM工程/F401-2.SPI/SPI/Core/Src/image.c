/*
 * @Author: your name
 * @Date: 2022-01-17 11:54:18
 * @LastEditTime: 2022-01-18 10:53:22
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \SPI\Core\Src\image.c
 */
#include <image.h>
#include <Code.h>
#include "draw_api.h"
unsigned char tmp_set[4];
void Draw_circle(unsigned char a, unsigned char b, unsigned char R, unsigned char wide)
{
    unsigned char x, y;
    unsigned int count = 0;

    count = 0;
    for (y = 0; y <= 64; y++)
    {
        for (x = 0; x <= 128; x++)
        {
            if (((x - a) * (x - a) + (y - b) * (y - b)) <= (R * R) &&
                ((x - a) * (x - a) + (y - b) * (y - b)) >= ((R - wide) * (R - wide)))
            {
                count++;
                buffer[x][y / 8] |= 0x01 << y % 8; //存档
                SetPixel(x, y);
            }
        }
    }
}
void Draw_Point(unsigned char a, unsigned char b, unsigned char R, unsigned char race)
{
    unsigned char x, y;
    unsigned char wide = 1;
    unsigned int count = 0, count2 = 0;
    int left, right, top, bottom;
    float u = 0;
    float a1, a2;
    for (y = 0; y <= 64; y++)
    {
        for (x = 0; x <= 128; x++)
        {
            if (((x - a) * (x - a) + (y - b) * (y - b)) <= (R * R) &&
                ((x - a) * (x - a) + (y - b) * (y - b)) >= ((R - wide) * (R - wide)))
            {
                count++;
            }
        }
    }
    a1 = count;
    if(race==0){
        OLED_Line(a, b, a, b-R);
        return;
    }
    if (race <= 25)
    {
        left = a;
        right = a + R;
        top = b - R;
        bottom = b;
        for (y = top; y <= bottom; y++)
        {
            for (x = left; x <= right; x++)
            {
                if (((x - a) * (x - a) + (y - b) * (y - b)) <= (R * R) &&
                    ((x - a) * (x - a) + (y - b) * (y - b)) >= ((R - wide) * (R - wide)))
                {
                    count2++;
                    a2 = count2;
                    u = a2 / a1 * 100;
                    if (u < race && u > race - 1)
                    {
                        OLED_Line(a, b, x, y);
                        return;
                    }
                }
            }
        }
    }
    else if (race > 25 && race <= 50)
    {
        count2 += count / 4;
        left = a;
        right = a + R;
        top = b;
        bottom = b + R;
        for (y = top; y <= bottom; y++)
        {
            for (x = right; x >= left; x--)
            {
                if (((x - a) * (x - a) + (y - b) * (y - b)) <= (R * R) &&
                    ((x - a) * (x - a) + (y - b) * (y - b)) >= ((R - wide) * (R - wide)))
                {
                    count2++;
                    a2 = count2;
                    u = a2 / a1 * 100;
                    if (u < race && u > race - 1)
                    {
                        OLED_Line(a, b, x, y);
                        return;
                    }
                }
            }
        }
    }
    else if (race > 50 && race <= 75)
    {
        count2 += count / 2;
        left = a - R;
        right = a;
        top = b;
        bottom = b + R;
        for (y = bottom; y >= top; y--)
        {
            for (x = right; x >= left; x--)
            {
                if (((x - a) * (x - a) + (y - b) * (y - b)) <= (R * R) &&
                    ((x - a) * (x - a) + (y - b) * (y - b)) >= ((R - wide) * (R - wide)))
                {
                    count2++;
                    a2 = count2;
                    u = a2 / a1 * 100;
                    if (u < race && u > race - 1)
                    {
                        OLED_Line(a, b, x, y);
                        return;
                    }
                }
            }
        }
    }
    else
    {
        count2 += count / 4 * 3;
        left = a - R;
        right = a;
        top = b - R;
        bottom = b;
        for (y = bottom; y >= top; y--)
        {
            for (x = left; x <= right; x++)
            {
                if (((x - a) * (x - a) + (y - b) * (y - b)) <= (R * R) &&
                    ((x - a) * (x - a) + (y - b) * (y - b)) >= ((R - wide) * (R - wide)))
                {
                    count2++;
                    a2 = count2;
                    u = a2 / a1 * 100;
                    if (u < race && u > race - 1)
                    {
                        OLED_Line(a, b, x, y);
                        return;
                    }
                }
            }
        }
    }
}
void Draw_Line(unsigned char upperX, unsigned char upperY, unsigned char bottomX, unsigned char bottomY, int mode)
{
    unsigned char x, y;
    int TupperY = upperY, TbottomY = bottomY, TupperX = upperX, TbottomX = bottomX;
    tmp_set[0] = upperX;
    tmp_set[1] = upperY;
    tmp_set[2] = bottomX;
    tmp_set[3] = bottomY;
    if (upperX > bottomX)
    {
        x = upperX;
        upperX = bottomX;
        bottomX = x;
    }
    if (upperY > bottomY)
    {
        y = upperY;
        upperY = bottomY;
        bottomY = y;
    }
    if (TupperY == TbottomY)
    {
        for (; upperX <= bottomX; upperX++)
        {
            if (mode == WRITE)
            {
                SetPixel(upperX, upperY);
            }
            else if (mode == CLEAN)
            {
                CleanPixel(upperX, upperY);
            }
        }
        return;
    }
    if (TupperX == TbottomX)
    {
        for (; upperY <= bottomY; upperY++)
        {
            if (mode == WRITE)
            {
                SetPixel(upperX, upperY);
            }
            else if (mode == CLEAN)
            {
                CleanPixel(upperX, upperY);
            }
        }
        return;
    }
    for (y = upperY; y <= bottomY; y++)
    {
        for (x = upperX; x <= bottomX; x++)
        {
            if (y == ((TupperY - TbottomY) / (TupperX - TbottomX) * (x - TupperX)))
            {
                if (mode == WRITE)
                {
                    count++;
                    SetPixel(x, y);
                }
                else if (mode == CLEAN)
                {
                    CleanPixel(x, y);
                }
            }
        }
    }
}
void Clean_line(void)
{
    Draw_Line(tmp_set[0], tmp_set[1], tmp_set[2], tmp_set[3], CLEAN);
}