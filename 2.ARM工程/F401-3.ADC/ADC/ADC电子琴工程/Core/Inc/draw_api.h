#ifndef DRAW_API_H
#define DRAW_API_H
#include "oled_config.h"
#include "oled_driver.h"
#include "oled_draw.h"
#include "oled_basic.h"
#include "oled_color.h"
#include "oled_buffer.h"
#include "oled_font.h"
#include "oled_bmp.h"

//����:��ʼ��ͼ�ο�
void InitGraph(void);
//����:����Ļ���ݸ��µ��豸��
void OLED_UpdateScreen(void);
//����:����
void OLED_ClearScreen(void);
//�뽫�˺�������1ms�ж��Ϊͼ���ṩʱ��
void OledTimeMsFunc(void);

//����:���û��Ƶ���ɫ  pix_black:��ɫ��pix_white:��ɫ
extern void OLED_Set_DrawColor(Type_color value);
//����:��ȡ��ǰ���õĻ�����ɫ  pix_black:��ɫ��pix_white:��ɫ
extern Type_color GetDrawColor(void);
//����:����������ɫ  pix_black:��ɫ��pix_white:��ɫ
extern void OLED_Set_Fillcolor(Type_color value);
//����:��ȡ��ǰ���õ������ɫ  pix_black:��ɫ��pix_white:��ɫ
extern Type_color GetFillColor(void);


/////////////////////////////////////////////////////////////////////////////////////////////////////
//���º���Ϊoled.draw��ֱ�ӹ��û����õĺ���

//���ܣ�����һ����
extern void OLED_Pixel(int x,int y);
//���ܣ���ȡһ�����ص����ɫ
extern Type_color GetPixel(int x,int y);

//����:����һ��������
extern void OLED_Line(int x1,int y1,int x2,int y2);
//����:���ٻ���һ��ˮƽ�� wΪ����
extern void OLED_FastHLine(int x, int y, unsigned char w);
//����:���ٻ���һ����ֱ��
extern void OLED_FastVLine(int x, int y, unsigned char h);
//����:�������� ���� numΪ�۵����
void OLED_PolyLineTo(const TypeXY *points,int num);

//����:ʹ�öԽǵ���ƾ���
extern void OLED_Rect1(int left,int top,int right,int bottom);
//����:ʹ�öԽǵ�������
extern void OLED_FillRect1(int left,int top,int right,int bottom);
//����:ʹ�ö��� ��߻��ƾ���
extern void OLED_Rect2(int left,int top,int width,int height);
//����:ʹ�ö��� ���������
extern void OLED_FillRect2(int left,int top,int width,int height);

//����:����һ��Բ
extern void OLED_Circle( int usX_Center, int usY_Center, int usRadius);
//����:����һ��ʵ��Բ
extern void OLED_FillCircle( int usX_Center, int usY_Center, int usRadius);
//����:4��֮һԲҪ����һ�ݻ��ļ���
extern void OLED_CircleHelper(int x0, int y0, unsigned char r, unsigned char cornername);
//����://���2���ķ�֮һԲ���м�ľ��� (ר�ú��� ������ע��)
extern void OLED_FillCircleHelper(int x0, int y0, unsigned char r, unsigned char cornername, int delta);

//����:����һ��Բ��(���Ż�)
extern void OLED_Arc(int x,int y,unsigned char r,int angle_start,int angle_end);
//����:���һ��Բ��(������)
extern void OLED_FillArc(int x,int y,unsigned char r,int angle_start,int angle_end);

//����:����һ��Բ�Ǿ���
extern void OLED_RoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r);
//����:����һ�����Բ�Ǿ���
extern void OLED_FillRoundRect(int x, int y, unsigned char w, unsigned char h, unsigned char r);

//����:����һ����Բ
extern void OLED_Ellipse(int x0,int y0,int a,int b);
//����:����һ�������Բ
extern void OLED_FillEllipse(int x0,int y0,int a,int b);
//����:����һ������������Բ
extern void OLED_EllipseRect( int x0, int y0, int x1, int y1);

//����:����һ��������
extern void OLED_Triangle(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
//����:����һ�����������
extern void OLED_FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2);

//����:����һ��ͼƬ bitmapΪͼƬ���ݣ���ͨ��ȡģ��ȡ��
extern void OLED_Bitmap(int x, int y, const unsigned char *bitmap, unsigned char w, unsigned char h);


//����:���������С  0 1 2 3
extern void OLED_Set_FontSize(unsigned char value);
//����:��ȡ�����С
extern unsigned char GetFontSize(void);
//����:��������ַ�ʱ�ı�����ɫ
extern void OLED_Set_TextBkMode(Type_textbk value);
//����:��ȡ����ַ�ʱ�ı�����ɫ
extern Type_textbk GetTextBkMode(void);
//����:����һ���ַ� �����:��size=0ʱ xΪ0-7s���� yΪ0-127��
extern void OLED_Char(int x, int y, unsigned char c);
////��ʾ����
extern void OLED_GBString(unsigned char x,unsigned char y,unsigned char *text);
extern void OLED_Printf(unsigned char Printf_Flag, unsigned char x, unsigned char y, char *fmt, ...);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//���º���Ϊoled.basic��ֱ�ӹ��û����õĺ���


//����:���������һ�����ͼ��(���������Բ���зǳ��ʺ�ʹ��)
extern void FloodFill2(unsigned char x,unsigned char y,int oldcolor,int newcolor);
//����:�ƶ���������
extern void MoveTo(int x,int y);
//����:���Ի���,�������������ƶ�����һ������(�ڻ��������б�����)
extern void LineTo(int x,int y);
//����:��ȡ��ǰ����Ƶ��y����
extern int GetY(void);
//����:��ȡ��ǰ����Ƶ��X����
extern int GetX(void);
//����:��ȡ��ǰ����Ƶ��X��Y����
extern TypeXY GetXY(void);

//����:������ת���ĵ�
extern void SetRotateCenter(int x0,int y0);
//����:������ת�Ƕ�
extern void SetAngle(double angle);
//����:������ת����
extern void SetAnggleDir(int direction);
//����:���ýǶȡ���ת������ת����
extern void SetRotateValue(int x,int y,float angle,int direct);
//����:��һ��������תһ���Ƕ�
extern TypeXY GetRotateXY(int x,int y);



//��Ļ���ݻ���
extern void SetScreenBuffer(void);
//����:�����µĻ�����Ϊ��Ļ���ݣ�
extern void SetTempBuffer(void);
//����:��ȡ��ǰ�Ļ���buffer��ϵ�� ���ػ���ϵ��SCREEN_BUFFER��TEMP_BUFFER
extern unsigned char GetSelectedBuffer(void);
//����:�����Ĭ�ϵ���Ļ��������
extern void OLED_ClearScreenBuffer(unsigned char val);
//����:�������ʱ����Ļ��������
extern void ClearTempBuffer(void);
//����:��ʱ����Ĺ���
extern void TempBufferFunc(int func);
//����:�̶�֡ˢ��
extern unsigned char FrameRateOLED_UpdateScreen(int value);

#endif

