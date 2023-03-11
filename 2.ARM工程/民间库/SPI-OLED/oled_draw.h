#ifndef OLED_DRAW_H
#define OLED_DRAW_H
#include "oled_basic.h"
#include "oled_color.h"

#define PRINT_NOW 1
#define PRINT_LATER 0
void OLED_Pixel(int x,int y);
void OLED_Line(int x1,int y1,int x2,int y2);
void OLED_FastHLine(int x, int y, unsigned char w);
void OLED_FastVLine(int x, int y, unsigned char h);
void OLED_PolyLineTo(const TypeXY *points,int num);
void OLED_FillRect1(int left,int top,int right,int bottom);
void OLED_Rect1(int left,int top,int right,int bottom);
void OLED_FillRect2(int left,int top,int width,int height);
void OLED_Rect2(int left,int top,int width,int height);
void OLED_Circle( int usX_Center, int usY_Center, int usRadius);
void OLED_FillCircle( int usX_Center, int usY_Center, int usRadius);
void OLED_CircleHelper(int x0, int y0, unsigned char r, unsigned char cornername);
void OLED_FillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta);
void OLED_Arc(int x,int y,unsigned char r,int angle_start,int angle_end);
void OLED_FillArc(int x,int y,unsigned char r,int angle_start,int angle_end);
void OLED_RoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r);
void OLED_FillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r);
void OLED_Ellipse(int x0,int y0,int a,int b);
void OLED_FillEllipse(int x0,int y0,int a,int b);
void OLED_EllipseRect( int x0, int y0, int x1, int y1);
void OLED_Triangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
void OLED_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);
void OLED_Bitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);
void DrawSlowBitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);
void OLED_Char(int x, int y, unsigned char c);
void OLED_String(int x, int y,char *str);
void OLED_GBString(unsigned char x,unsigned char y,unsigned char *text);
void OLED_Printf(unsigned char Printf_Flag, unsigned char x, unsigned char y, char *fmt, ...);

Type_color GetPixel(int x,int y);
int GetY(void);
int GetX(void);
TypeXY GetXY(void);
void MoveTo(int x,int y);
void LineTo(int x,int y);
#endif

