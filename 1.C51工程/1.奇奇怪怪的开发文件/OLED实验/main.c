//////////////////////////////////////////////////////////////////////////////////         
//云殻會峪工僥楼聞喘��隆将恬宀俯辛��音誼喘噐凪万販採喘余
//嶄尚坩窮徨
//  猟 周 兆   : main.c
//  井 云 催   : v2.0
//  恬    宀   : HuangKai
//  伏撹晩豚   : 2014-0101
//  恷除俐個   :
//  孔嬬宙峰   : OLED IIC俊笥處幣箭殻(51狼双)
// 俐個煽雰   :
// 晩    豚   :
// 恬    宀   : HuangKai
// 俐個坪否   : 幹秀猟周
//井幡侭嗤��義井駅梢。
//Copyright(C) 嶄尚坩窮徨2014/3/16
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
        Write_IIC_Command(0xAE);//display off�┨慙塋升�||0xAE購液徳鳥
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0x20);//Set Memory Addressing Mode��譜崔坪贋儖峽庁塀��       
        Write_IIC_Command(0x10);//��00��邦峠儖峽庁塀��01��換岷儖峽圭塀��10、匈中儖峽庁塀�┯肝撮���11��涙丼��
															  //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xb0);/*(譜崔匈中儖峽庁塀議匈中軟兵仇峽��0-7)
																Set Page Start Address for Page Addressing Mode,0-7*/
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xc8);//(譜崔COM補竃膝宙圭��)Set COM Output Scan Direction
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0x00);//---(譜崔詰双仇峽)set low column address
        Write_IIC_Command(0x10);//---(譜崔互双仇峽)set high column address
        Write_IIC_Command(0x40);//--��譜崔軟兵佩仇峽��set start line address
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0x81);//--��譜崔斤曳業陣崙篠贋匂��set contrast control register
        Write_IIC_Command(0x7f);/*譜崔斤曳業 ��81H+A[7:0]��
																	宸頁匯訳褒忖准峺綜��喇及屈訳峺綜峺協勣譜崔議斤曳業雫方。
																	A[7:0] 貫 00H~FFH 蛍艶峺協斤曳業葎 1~256 雫。SEG�╋裡�
																	補竃議窮送寄弌昧斤曳業雫方議奐紗遇奐紗。*/
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xa1);//--�┰�粁嶷仟啌符0譜崔葎127��set segment re-map 0 to 127
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xa6);//--��譜崔屎械�塋升�set normal display
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xa8);//--��譜崔謹揃鹸喘曳楕��1欺64����set multiplex ratio(1 to 64)
        Write_IIC_Command(0x3F);/*譜崔鹸喘楕 ��A8H+A[5:0]��
																	宸頁匯訳褒忖准峺綜��喇A[5:0]峺協勣譜崔議鹸喘楕
																	鹸喘楕��MUX ratio��軸僉宥議COM佩方��音嬬詰噐16��
																	宥狛A[5:0]栖峺協。
																	A[5:0] 互曾了涙号協篇葎0��侭參及屈訳峺綜貫 0FH~3FH 
																	議函峙譜崔鹸喘楕葎 1~64�┝�A[5:0]+1��。A[5:0]貫0欺14議函峙脅頁涙丼議。*/
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xa4);//��0xa4��補竃効昧RAM坪否��0xa5��補竃策待RAM坪否��0xa4,Output follows RAM content;0xa5,Output ignores RAM content
        Write_IIC_Command(0xd3);//-��譜崔�塋焼�卞楚��set display offset
        Write_IIC_Command(0x00);//-��短嗤陶卞楚��not offset
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xd5);//--��譜崔�塋省疫啖崙輝�/尅鬼匂撞楕C��set display clock divide ratio/oscillator frequency
        Write_IIC_Command(0xf0);//--��譜協蛍護曳楕��set divide ratio
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xd9);//--��譜崔圓割窮巓豚 ��D9H+A[7:0]����set pre-charge period
        Write_IIC_Command(0x22);//
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xda);//--��譜崔com哈重啣周塘崔��set com pins hardware configuration
        Write_IIC_Command(0x12);/*6.譜崔COM啣周塘崔 ��DAH+A[5:4]��
																	宸頁匯訳褒忖准峺綜��喇A[5:4]序佩譜崔。
																	A[5] 了譜崔COM恣嘔郡崔��A[4] 喘栖譜崔會双/姥僉哈重塘崔��凪麿了嗤号協��*/
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0xdb);//--��3.譜崔VCOMH補竃議互窮峠 ��DBH+A[6:4]����set vcomh
        Write_IIC_Command(0x20);//0x20,0.77xVcc
		/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
        Write_IIC_Command(0x8d);//--��聞嬬DC-DC庁翠��set DC-DC enable
        Write_IIC_Command(0x14);//
        Write_IIC_Command(0xaf);//--�┫鮨�oled中医��turn on oled panel
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
                Write_IIC_Command(0x00);                //詰 双 軟兵仇峽
                Write_IIC_Command(0x10);                //互双 軟兵仇峽
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
void display(unsigned char  x,unsigned char  y,unsigned char* hok){//x=0~7;y=0~7;hok�駛�=8x8
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
