#ifndef __OLED_H
#define __OLED_H

#include "main.h"

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16


extern  const unsigned char PROGMEM logo_bmp[32];
extern void Display_init();
extern void Display(String data);


extern const unsigned char PROGMEM Cat[134];
extern const unsigned char PROGMEM Cat_2[640];/* (76 X 64 )*/
extern const unsigned char PROGMEM Shi_Zhong[2][32];//时钟 16x16
extern const unsigned char PROGMEM Cat_3[704];/* (82 X 64 )*/
extern const unsigned char PROGMEM Bu_Shu[2][32];//步数 16x16
#endif