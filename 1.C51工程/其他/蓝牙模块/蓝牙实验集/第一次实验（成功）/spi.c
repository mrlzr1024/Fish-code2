#include"spi.h"
#include<reg52.h>
int font6x8[][6]={ 0x04,0x1C,0x3E,0x3E,0x1C,0x04 };
int blank[][6]={0x00,0x00,0x00,0x00,0x00,0x00};
void delay_1us(void){
}
/***********************************************************

函数名称：LCD_write_byte

函数功能：模拟SPI接口时序写数据/命令LCD

入口参数：data    ：写入的数据；

          command ：写数据/命令选择；

出口参数：无

备 注：

***********************************************************/
void LCD_write_byte(unsigned char dat, unsigned char command){
  

    unsigned char i;

    LCD_CE = 0;                              //5110片选有效，允许输入数据

    if (command == 0)                        //写命令

         LCD_DC = 0;                         

    else  LCD_DC = 1;                    //写数据

      for(i=0;i<8;i++)                            //传送8bit数据

            {

if(dat&0x80)

                        SDIN = 1;

                  else

                        SDIN = 0;

                  SCLK = 0;

                  dat = dat << 1;

                  SCLK = 1;

}

     LCD_CE = 1;                                //禁止5110

  }
/***********************************************************

函数名称：LCD_clear

函数功能：清屏Nakia5110

入口参数：无

出口参数：无

备 注：

***********************************************************/
void LCD_clear(void){
    unsigned int i;

    LCD_write_byte(0x0c, 0);//普通显示模式			
    LCD_write_byte(0x80, 0);//x起始坐标		

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);			
  }

  /***********************************************************

函数名称：LCD_init

函数功能：5110初始化

入口参数：无

出口参数：无

备 注：

***********************************************************/

void LCD_init(void){

    LCD_RST = 0;     // 产生一个让LCD复位的低电平脉冲

    delay_1us();

    LCD_RST = 1;

    LCD_CE = 0;     // 关闭LCD

    delay_1us();

    LCD_CE = 1;     // 使能LCD

    delay_1us();

    LCD_write_byte(0x21, 0);      // 使用扩展命令设置LCD模式

    LCD_write_byte(0xBD, 0);      // 设置液晶偏置电压，对比度调整

    LCD_write_byte(0x06, 0);      // 温度校正

    LCD_write_byte(0x13, 0);      // 1:48

    LCD_write_byte(0x20, 0);      // 使用基本命令，V=0，水平寻址

    LCD_clear();                 // 清屏

    LCD_write_byte(0x0c, 0);      // 设定显示模式，正常显示

    LCD_CE = 0;      // 关闭LCD
}
  
/***********************************************************

函数名称：LCD_set_XY

函数功能：设置LCD初始坐标函数

入口参数：X       ：0－83

          Y       ：0－5

出口参数：无

备 注：

***********************************************************/
void LCD_set_XY(unsigned char X, unsigned char Y){
  
   LCD_write_byte(0x40 | Y, 0);              // 行

   LCD_write_byte(0x80 | X, 0);        // 列

  }
/***********************************************************

函数名称：LCD_write_char

函数功能：显示英文字符

入口参数：c      :  显示的字符

出口参数：无

备 注：

***********************************************************/
void LCD_write_char(int h[][6]){

    unsigned char line;

//    c -= 32;                       //数组的行号

    for (line=0; line<6; line++)

        LCD_write_byte(h[0][line], 1);

}

void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map, unsigned char Pix_x,unsigned char Pix_y){
    unsigned int i,n;
    unsigned char row;//计算位图所占行数
      if (Pix_y%8==0)             //如果为位图所占行数为整数
           row=Pix_y/8;     
      else
         row=Pix_y/8+1;            //如果为位图所占行数不是整数
      LCD_set_XY(X,Y);
    for (n=0;n<row;n++)            //换行
      {     
        for(i=0;i<Pix_x;i++)
          {     
                 LCD_set_XY(X+i,Y+n);
             LCD_write_byte(map[i+n*Pix_x], 1);
          }                        
      }     
}
void display(unsigned char x,unsigned char y,int h[][6]){
  LCD_set_XY(x,y);
  LCD_write_char(h);
}