//////////////////////////////////////////////////////////////////////////////////         
//±¾³ÌÐòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßÐí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ÖÐ¾°Ô°µç×Ó
//  ÎÄ ¼þ Ãû   : main.c
//  °æ ±¾ ºÅ   : v2.0
//  ×÷    Õß   : HuangKai
//  Éú³ÉÈÕÆÚ   : 2014-0101
//  ×î½üÐÞ¸Ä   :
//  ¹¦ÄÜÃèÊö   : OLED IIC½Ó¿ÚÑÝÊ¾Àý³Ì(51ÏµÁÐ)
// ÐÞ¸ÄÀúÊ·   :
// ÈÕ    ÆÚ   :
// ×÷    Õß   : HuangKai
// ÐÞ¸ÄÄÚÈÝ   : ´´½¨ÎÄ¼þ
//°æÈ¨ËùÓÐ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ÖÐ¾°Ô°µç×Ó2014/3/16
//All rights reserved
//******************************************************************************/
#include "reg52.h"
#include<string.h>
#define high 1
#define low 0
/*************Pin Define***************/
sbit SCL=P3^6;
sbit SDA=P3^7;
/****************************************************/
void Initial_LY096BG30();
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture_1();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
/***********************Initial code*********************/
void Initial_LY096BG30()
{
        Write_IIC_Command(0xAE);//display off£¨¹ØÏÔÊ¾£©||0xAE¹Ø±ÕÆÁÄ»
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0x20);//Set Memory Addressing Mode£¨ÉèÖÃÄÚ´æÑ°Ö·Ä£Ê½£©       
        Write_IIC_Command(0x10);//£¨00£¬Ë®Æ½Ñ°Ö·Ä£Ê½£»01£¬´¹Ö±Ñ°Ö··½Ê½£»10¡¢Ò³ÃæÑ°Ö·Ä£Ê½£¨¸´Î»£©£»11£¬ÎÞÐ§£©
															  //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xb0);/*(ÉèÖÃÒ³ÃæÑ°Ö·Ä£Ê½µÄÒ³ÃæÆðÊ¼µØÖ·£¬0-7)
																Set Page Start Address for Page Addressing Mode,0-7*/
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xc8);//(ÉèÖÃCOMÊä³öÉ¨Ãè·½Ïò)Set COM Output Scan Direction
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0x00);//---(ÉèÖÃµÍÁÐµØÖ·)set low column address
        Write_IIC_Command(0x10);//---(ÉèÖÃ¸ßÁÐµØÖ·)set high column address
        Write_IIC_Command(0x40);//--£¨ÉèÖÃÆðÊ¼ÐÐµØÖ·£©set start line address
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0x81);//--£¨ÉèÖÃ¶Ô±È¶È¿ØÖÆ¼Ä´æÆ÷£©set contrast control register
        Write_IIC_Command(0x7f);/*ÉèÖÃ¶Ô±È¶È £¨81H+A[7:0]£©
																	ÕâÊÇÒ»ÌõË«×Ö½ÚÖ¸Áî£¬ÓÉµÚ¶þÌõÖ¸ÁîÖ¸¶¨ÒªÉèÖÃµÄ¶Ô±È¶È¼¶Êý¡£
																	A[7:0] ´Ó 00H~FFH ·Ö±ðÖ¸¶¨¶Ô±È¶ÈÎª 1~256 ¼¶¡£SEG£¨¶Î£©
																	Êä³öµÄµçÁ÷´óÐ¡Ëæ¶Ô±È¶È¼¶ÊýµÄÔö¼Ó¶øÔö¼Ó¡£*/
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xa1);//--£¨½«¶ÎÖØÐÂÓ³Éä0ÉèÖÃÎª127£©set segment re-map 0 to 127
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xa6);//--£¨ÉèÖÃÕý³£ÏÔÊ¾£©set normal display
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xa8);//--£¨ÉèÖÃ¶àÂ·¸´ÓÃ±ÈÂÊ£¨1µ½64£©£©set multiplex ratio(1 to 64)
        Write_IIC_Command(0x3F);/*ÉèÖÃ¸´ÓÃÂÊ £¨A8H+A[5:0]£©
																	ÕâÊÇÒ»ÌõË«×Ö½ÚÖ¸Áî£¬ÓÉA[5:0]Ö¸¶¨ÒªÉèÖÃµÄ¸´ÓÃÂÊ
																	¸´ÓÃÂÊ£¨MUX ratio£©¼´Ñ¡Í¨µÄCOMÐÐÊý£¬²»ÄÜµÍÓÚ16£¬
																	Í¨¹ýA[5:0]À´Ö¸¶¨¡£
																	A[5:0] ¸ßÁ½Î»ÎÞ¹æ¶¨ÊÓÎª0£¬ËùÒÔµÚ¶þÌõÖ¸Áî´Ó 0FH~3FH 
																	µÄÈ¡ÖµÉèÖÃ¸´ÓÃÂÊÎª 1~64£¨¼´A[5:0]+1£©¡£A[5:0]´Ó0µ½14µÄÈ¡Öµ¶¼ÊÇÎÞÐ§µÄ¡£*/
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xa4);//£¨0xa4£¬Êä³ö¸úËæRAMÄÚÈÝ£»0xa5£¬Êä³öºöÂÔRAMÄÚÈÝ£©0xa4,Output follows RAM content;0xa5,Output ignores RAM content
        Write_IIC_Command(0xd3);//-£¨ÉèÖÃÏÔÊ¾Æ«ÒÆÁ¿£©set display offset
        Write_IIC_Command(0x00);//-£¨Ã»ÓÐÆ«ÒÆÁ¿£©not offset
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xd5);//--£¨ÉèÖÃÏÔÊ¾Ê±ÖÓ·ÖÆµ±È/Õñµ´Æ÷ÆµÂÊC£©set display clock divide ratio/oscillator frequency
        Write_IIC_Command(0xf0);//--£¨Éè¶¨·Ö¸î±ÈÂÊ£©set divide ratio
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xd9);//--£¨ÉèÖÃÔ¤³äµçÖÜÆÚ £¨D9H+A[7:0]£©£©set pre-charge period
        Write_IIC_Command(0x22);//
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xda);//--£¨ÉèÖÃcomÒý½ÅÓ²¼þÅäÖÃ£©set com pins hardware configuration
        Write_IIC_Command(0x12);/*6.ÉèÖÃCOMÓ²¼þÅäÖÃ £¨DAH+A[5:4]£©
																	ÕâÊÇÒ»ÌõË«×Ö½ÚÖ¸Áî£¬ÓÉA[5:4]½øÐÐÉèÖÃ¡£
																	A[5] Î»ÉèÖÃCOM×óÓÒ·´ÖÃ£¬A[4] ÓÃÀ´ÉèÖÃÐòÁÐ/±¸Ñ¡Òý½ÅÅäÖÃ£¬ÆäËûÎ»ÓÐ¹æ¶¨£¬*/
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0xdb);//--£¨3.ÉèÖÃVCOMHÊä³öµÄ¸ßµçÆ½ £¨DBH+A[6:4]£©£©set vcomh
        Write_IIC_Command(0x20);//0x20,0.77xVcc
		/*¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª*/
        Write_IIC_Command(0x8d);//--£¨Ê¹ÄÜDC-DCÄ£¿é£©set DC-DC enable
        Write_IIC_Command(0x14);//
        Write_IIC_Command(0xaf);//--£¨´ò¿ªoledÃæ°å£©turn on oled panel
}
/***********************Picture Code**************************/
unsigned char code show1[]=
{

0x78,0x4E,0x42,0x42,0x42,0x42,0x4E,0x78,0x78,0x4E,0x42,0x42,0x42,0x42,0x4E,0x78
	
};
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
   SCL = high;
   //Delay_us(1);               
   SDA = high;
   //Delay_us(1);
   SDA = low;
  // Delay_us(1);
   SCL = low;
  // Delay_us(1);
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
   SCL = low;
   //Delay_us(1);
   SDA = low;
   //Delay_us(1);
   SCL = high;
   //Delay_us(1);
   SDA = high;
   //Delay_us(1);
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
        unsigned char i;
        for(i=0;i<8;i++)               
        {
                if(IIC_Byte & 0x80)                //1?0?
                SDA=high;
                else
                SDA=low;
                //Delay_us(1);
                SCL=high;
                //Delay_us(1);
                SCL=low;
                //Delay_us(1);
                IIC_Byte<<=1;                        //loop
        }
        SDA=1;
        //Delay_us(1);
        SCL=1;
        //Delay_us(1);
        SCL=0;
        //Delay_us(1);
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);                        //write command
   Write_IIC_Byte(IIC_Command);
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);                       
   Write_IIC_Byte(0x40);                        //write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop();
}
/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
        unsigned char m,n;
        for(m=0;m<8;m++)
        {
                Write_IIC_Command(0xb0+m);                //page0-page1
                Write_IIC_Command(0x00);                //µÍ ÁÐ ÆðÊ¼µØÖ·
                Write_IIC_Command(0x10);                //¸ßÁÐ ÆðÊ¼µØÖ·
                for(n=0;n<128;n++)
                        {
                                Write_IIC_Data(fill_Data);
                        }
        }
}
/******************************************
// picture
******************************************/
/*void picture_1()
//{
//	unsigned char y;
//  unsigned char i=0;
//  for(y=0;y<8;y++)
//    {
//      Write_IIC_Command(0xb0+y);//
//      Write_IIC_Command(0x00);
//      Write_IIC_Command(0x10);
//      for(i=0;i<16;i++)
//        {
//          Write_IIC_Data(show1[i++]);
//        }
//				i=0;
//    }
//}
*/
void display(unsigned char  x,unsigned char  y,unsigned char* hok){//x=0~7;y=0~7;hokÏñËØ=8x8
	unsigned int i=0;
      Write_IIC_Command(0xb0+y);//
      Write_IIC_Command(((x&0xf0)>>4)|0x00);
      Write_IIC_Command((x&0x0f)|0x10);
      for(i=0;i<12;i++)
        {
          Write_IIC_Data(hok[i]);
        }
}
/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)                //
{
        unsigned int m;
        for(;Del_50ms>0;Del_50ms--)
                for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)                //
{
        unsigned char j;
        while(Del_1ms--)
        {       
                for(j=0;j<123;j++);
        }
}
/*******************************Main*******************************/
void main(void)
{
	int i=0;
        Initial_LY096BG30();
        Delay_1ms(5);
	         fill_picture(0x00);   

        while(1)
        {
					display(i,4,show1);			
							i++;
					if(i>=8){i=0;}					
        }
}
