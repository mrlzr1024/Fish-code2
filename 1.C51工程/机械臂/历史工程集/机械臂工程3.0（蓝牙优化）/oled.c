#include "oled.h"
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
/***********************Initial code主初始化屏幕*********************/
void Initial_LY096BG30()
{
    Write_IIC_Command(0xAE); //display off（关显示）||0xAE关闭屏幕
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0x20); //Set Memory Addressing Mode（设置内存寻址模式）
    Write_IIC_Command(0x10); //（00，水平寻址模式；01，垂直寻址方式；10、页面寻址模式（复位）；11，无效）
                             //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xb0); /*(设置页面寻址模式的页面起始地址，0-7)
																Set Page Start Address for Page Addressing Mode,0-7*/
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xc8); //(设置COM输出扫描方向)Set COM Output Scan Direction
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0x00); //---(设置低列地址)set low column address
    Write_IIC_Command(0x10); //---(设置高列地址)set high column address
    Write_IIC_Command(0x40); //--（设置起始行地址）set start line address
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0x81); //--（设置对比度控制寄存器）set contrast control register
    Write_IIC_Command(0x7f); /*设置对比度 （81H+A[7:0]）
																	这是一条双字节指令，由第二条指令指定要设置的对比度级数。
																	A[7:0] 从 00H~FFH 分别指定对比度为 1~256 级。SEG（段）
																	输出的电流大小随对比度级数的增加而增加。*/
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xa1); //--（将段重新映射0设置为127）set segment re-map 0 to 127
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xa6); //--（设置正常显示）set normal display
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xa8); //--（设置多路复用比率（1到64））set multiplex ratio(1 to 64)
    Write_IIC_Command(0x3F); /*设置复用率 （A8H+A[5:0]）
																	这是一条双字节指令，由A[5:0]指定要设置的复用率
																	复用率（MUX ratio）即选通的COM行数，不能低于16，
																	通过A[5:0]来指定。
																	A[5:0] 高两位无规定视为0，所以第二条指令从 0FH~3FH 
																	的取值设置复用率为 1~64（即A[5:0]+1）。A[5:0]从0到14的取值都是无效的。*/
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xa4); //（0xa4，输出跟随RAM内容；0xa5，输出忽略RAM内容）0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    Write_IIC_Command(0xd3); //-（设置显示偏移量）set display offset
    Write_IIC_Command(0x00); //-（没有偏移量）not offset
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xd5); //--（设置显示时钟分频比/振荡器频率C）set display clock divide ratio/oscillator frequency
    Write_IIC_Command(0xf0); //--（设定分割比率）set divide ratio
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xd9); //--（设置预充电周期 （D9H+A[7:0]））set pre-charge period
    Write_IIC_Command(0x22); //
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xda); //--（设置com引脚硬件配置）set com pins hardware configuration
    Write_IIC_Command(0x12); /*6.设置COM硬件配置 （DAH+A[5:4]）
																	这是一条双字节指令，由A[5:4]进行设置。
																	A[5] 位设置COM左右反置，A[4] 用来设置序列/备选引脚配置，其他位有规定，*/
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0xdb); //--（3.设置VCOMH输出的高电平 （DBH+A[6:4]））set vcomh
    Write_IIC_Command(0x20); //0x20,0.77xVcc
                             /*————————————————————————————————————————————————————————————————————————————————————————————————————————————————————*/
    Write_IIC_Command(0x8d); //--（使能DC-DC模块）set DC-DC enable
    Write_IIC_Command(0x14); //
    Write_IIC_Command(0xaf); //--（打开oled面板）turn on oled panel
}
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
    for (i = 0; i < 8; i++)
    {
        if (IIC_Byte & 0x80) //1?0?
            SDA = high;
        else
            SDA = low;
        //Delay_us(1);
        SCL = high;
        //Delay_us(1);
        SCL = low;
        //Delay_us(1);
        IIC_Byte <<= 1; //loop
    }
    SDA = 1;
    //Delay_us(1);
    SCL = 1;
    //Delay_us(1);
    SCL = 0;
    //Delay_us(1);
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
    IIC_Start();
    Write_IIC_Byte(0x78); //Slave address,SA0=0
    Write_IIC_Byte(0x00); //write command
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
    Write_IIC_Byte(0x40); //write data
    Write_IIC_Byte(IIC_Data);
    IIC_Stop();
}
/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
    unsigned char m, n;
    for (m = 0; m < 8; m++)
    {
        Write_IIC_Command(0xb0 + m); //page0-page1
        Write_IIC_Command(0x00);     //低 列 起始地址
        Write_IIC_Command(0x10);     //高列 起始地址
        for (n = 0; n < 128; n++)
        {
            Write_IIC_Data(fill_Data);
        }
    }
}
/******************************************
// picture
******************************************/
/* 函数名称：display(unsigned char x, unsigned char y, unsigned char *hok)
输入：x,y坐标，要显示的字符(hok)
输出：无
功能：在(x,y)上显示对应字符hok(一个)
备注：x=(0~7);
      y=(0~7);
      hok[]=8x8(像素)
 */
void display(unsigned char x, unsigned char y, unsigned char hok[][8],int num)
{ //x=0~7;y=0~7;hok像素=8x8
		int ten=0;
		int n=0;
			unsigned int i = 0; 
		ten=num/10;
		n=num%10;
    Write_IIC_Command(0xb0 + y); //
    Write_IIC_Command(0x00 + x);
    Write_IIC_Command(0x10 + x);
    for (i = 0; i < 8; i++)
    {
        Write_IIC_Data(hok[ten][i]);
    }
		for (i = 0; i < 8; i++)
    {
        Write_IIC_Data(hok[n][i]);
    }
}
/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms) //
{
    unsigned int m;
    for (; Del_50ms > 0; Del_50ms--)
        for (m = 6245; m > 0; m--)
            ;
}
void Delay_1ms(unsigned int Del_1ms) //
{
    unsigned char j;
    while (Del_1ms--)
    {
        for (j = 0; j < 123; j++)
            ;
    }
}
/*******************************Main*******************************/
/* 函数名称：oledInit(void)
输入：无
输出：无
功能：初始化oled屏幕
备注：无
 */
void oledInit(void)
{
    Initial_LY096BG30(); //初始化屏幕
    Delay_1ms(5);
    fill_picture(0x00); //清屏
}
/* void main(void)
// {
//    oledInit

//     while (1)
//     {
//         display(7, 4, show1);
//     }
// }
*/
