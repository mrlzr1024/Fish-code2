#ifndef OLED_COLOR_H
#define OLED_COLOR_H
//������ɫ���򵥻���or���ӻ���
#define  COLOR_CHOOSE_DRAW   (SIMPLE_DRAW)   


typedef enum
{
	pix_black,
	pix_white,
	//............
}Type_color;

//��ȡ��ǰ���õ����ص�ɫ
Type_color GetDrawColor(void);
//���ý�Ҫ���Ƶ����ص�ɫ
void OLED_Set_DrawColor(Type_color value);

Type_color GetFillColor(void);
void OLED_Set_Fillcolor(Type_color value);
#endif


