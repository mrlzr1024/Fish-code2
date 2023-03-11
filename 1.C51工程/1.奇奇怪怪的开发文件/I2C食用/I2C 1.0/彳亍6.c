#include <reg52.h>
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int        
sbit SCL = P2^0;
sbit SDA = P2^1;
char ADDR = 0x7e;   
//***************************** 延时 y  ms ***********************************************
void delay1(int y)   // 
{
         ;
        while(y--)
        {
        unsigned char a,b,c;
        for(c=1;c>0;c--)
        for(b=142;b>0;b--)
        for(a=2;a>0;a--);
        }
}
//******************************** IIC 串口开始 ********************************************
void IIC_start(void)
{
        SDA=1;
        _nop_();
        SCL=1;
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        SDA=0;
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        SCL=0;
}
//********************************** IIC 串口写1个字节 ******************************************
void IIC_writeByte(char temp)
{
        char i;
        for(i=0;i<8;i++)
        {
                SDA=(bit)(temp & 0x80) ;   // 根据规定1602的数据最高位必须为  1  
                temp <<=1;
                _nop_();
                _nop_();
                SCL=1;
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                _nop_();
                SCL=0;
        }
        _nop_(); 
        _nop_();
        _nop_();
        _nop_();
        SDA=1;
        _nop_(); 
        _nop_(); 
        _nop_();
        _nop_();
        SCL=1; 
        _nop_();
        _nop_();
        _nop_();
        while(SDA);
        _nop_();
        SCL=0;
}
//******************************** 1602写命令 ********************************************
void LCD_write_command(char comm)
{
        char tmp;
        IIC_start();          // 串口开始
        IIC_writeByte(ADDR);  // 先选PCF 8574T 的地址  （应该是相当于选中的意思吧）
        
        tmp = comm & 0xF0;    // 与0xf0 应该是取低四位的意思吧
        tmp |= 0x0C;         //保留高4位为指令的高四位，低四位为   RS = 0, RW = 0, EN = 1  
        IIC_writeByte(tmp);  //从串口送出
        delay1(20);
        tmp &= 0xFB;        //Make EN = 0
        IIC_writeByte(tmp); 
        
        tmp = (comm & 0x0F) << 4 ;  //将指令的低四位 送到高位置保存
        tmp |= 0x0C;        //RS = 0, RW = 0, EN = 1
        IIC_writeByte(tmp);
        delay1(20);
        tmp &= 0xFB; // Make EN = 0
        IIC_writeByte(tmp);
        
}
//******************************** 1602写数据 ********************************************
void LCD_write_data(char data1)
{
        char tmp;
        IIC_start();
        IIC_writeByte(ADDR);   // 先选PCF 8574T 的地址  （应该是相当于选中的意思吧）
        
        tmp = data1 & 0xF0;
        tmp |= 0x0D; //RS = 0, RW = 0, EN = 1
        IIC_writeByte(tmp);
        delay1(20);
        tmp &= 0xFB; //Make EN = 0
        IIC_writeByte(tmp); 
        
        tmp = (data1 & 0x0F) << 4 ;
        tmp |= 0x0D; //RS = 0, RW = 0, EN = 1
        IIC_writeByte(tmp);
        delay1(20);
        tmp &= 0xFB ; // Make EN = 0
        IIC_writeByte(tmp);
}
//******************************** 1602初始化 ********************************************
void Init_Lcd(void)
{
        LCD_write_command(0x33); //将8位总线转为4位总线
        delay1(50) ;
        LCD_write_command(0x32); //
        delay1(50) ; 
        LCD_write_command(0x28); // 4位数据线，显示2行，5*7点阵字符  ！如果是0x38  则为8位数据线，显示2行，5*7点阵字符
        delay1(50) ; 
        LCD_write_command(0x0C); // 开显示，关闭光标，不闪烁
        delay1(50) ;  
        LCD_write_command(0x06); // 设定输入方式，增量不位移
        delay1(50) ; 
        LCD_write_command(0x01); // 清屏
        delay1(50) ;
}
void main()
{
	Init_Lcd();
	LCD_write_data('1');
	while(1);
}