/*
 * @Author: your name
 * @Date: 2021-11-09 18:48:48
 * @LastEditTime: 2021-11-14 20:46:13
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \LED\src\main.c
 */
/*************************************
 * 
 *        89c52 sdcc blink demo
 * 
 * CPU: 89C52
 * FREQ: 12MHz
 * PIN: P00
 * 
 * ***********************************
*/

#include <reg52.h>
#include <stdio.h>

void delay_100ms(); //@12MHz

void main()
{
    bit a=0xfe&0x80;
    while (1)
    {
        P00 = !P00;
        delay_100ms();
    }
}

void delay_100ms()
{
    unsigned char i, j;

    i = 195;
    j = 138;

    do
    {
        while (--j)
            ;
    } while (--i);
}