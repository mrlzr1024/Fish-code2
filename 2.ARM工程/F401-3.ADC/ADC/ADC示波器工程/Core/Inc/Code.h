/*
 * @Author: LZR
 * @Date: 2022-01-16 17:14:48
 * @LastEditTime: 2022-01-18 16:25:19
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \SPI\Core\Inc\Code.h
 */
/*
 *@简明：此文件为OLED(128X64)的基础绘图文件
 *@包括：bmp:要放的图(若<128x64则需要使用Resize函数直接显示)
       ·Resize()函数显示大小小于128X64的位图，若大小为128x64则可以使用OLED_FILL()函数(oled_driver.h)显示
       ·SetPixel()函数：描点函数
       ·Clean()函数：清屏函数
*/
#ifndef __CODE_H
#define __CODE_H
#include <main.h>
extern unsigned char code0_9[][16];
extern unsigned char codea_g[][16];
extern unsigned char buffer[128][8]; //点缓冲区
extern void Resize(unsigned char *bmmp, int length, int wide, int odds);
extern void SetPixel(unsigned char x, unsigned char y);
extern void CleanPixel(unsigned char x, unsigned char y);
extern void Clean(void);
extern unsigned char Sbmp[1024];

#endif // !
