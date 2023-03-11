#include<reg51.h>
sbit P1_0=P1^0;//A
sbit P1_1=P1^1;//B
sbit P1_2=P1^2;//C
sbit P1_3=P1^3;//D
sbit P1_4=P1^4;//E
char i;
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

void InitTimer5(void)//0.5ms
{
    TMOD = 0x01;
    TH0 = 0x0FE;
    TL0 = 0x33;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer9(void)//0.9ms
{
    TMOD = 0x01;
    TH0 = 0x0FC;
    TL0 = 0x0C3;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer1(void)//1ms
{
    TMOD = 0x01;
    TH0 = 0x0FC;
    TL0 = 0x66;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer13(void)//1.3ms
{
    TMOD = 0x01;
    TH0 = 0x0FA;
    TL0 = 0x0EC;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer18(void) //1.8ms
{
    TMOD = 0x01;
    TH0 = 0x0F8;
    TL0 = 0x0F8;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer15(void)//1.5ms
{
    TMOD = 0x01;
    TH0 = 0x0FA;
    TL0 = 0x24;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer17(void)//1.7ms
{
    TMOD = 0x01;
    TH0 = 0x0F9;
    TL0 = 0x5C;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void InitTimer20(void)//2ms
{
    TMOD = 0x01;
    TH0 = 0x0F8;
    TL0 = 0x30;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void delay1s(void)   //1s
{
    unsigned char a,b,c;
    for(c=13;c>0;c--)
        for(b=247;b>0;b--)
            for(a=142;a>0;a--);
}

void delay20(void)   //延时20ms
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=222;b>0;b--)
            for(a=40;a>0;a--);
}
void left()
{
	P1_4=1;
	InitTimer5();
	delay20();
	delay1s();
	P1_0=1;
	InitTimer20();
	delay20();
	delay1s();
	 P1_2=1;
	InitTimer5();//
	delay20();
	delay1s();
	P1_3=1;
	InitTimer1();///
	delay20();
	delay1s();
	P1_0=1;
	InitTimer5();
	delay20();
	delay1s();
}
void right()
{
	P1_4=1;
	InitTimer15();
	delay20();
	delay1s();
	//P1_0=1;
	//InitTimer9();
	//delay20();
	//delay1s();
	P1_2=1;
	InitTimer9(); //
	delay20();
	delay1s();
	P1_1=1;
	InitTimer9();///
	delay20();
	delay1s();
	P1_0=1;
	InitTimer5();
	delay20();
	delay1s();

}
void init()
{
	P1_0=0;
	P1_1=0;
	P1_2=0;
	P1_3=0;
	P1_4=0;	
		
}
void delay5(void)   //误差 -0.000000000114us
{
    unsigned char a,b,c;
    for(c=98;c>0;c--)
        for(b=127;b>0;b--)
            for(a=17;a>0;a--);
}
void init2()
{
	P1_0=1;
	InitTimer5();
	delay20();
	delay1s();
	P1_2=1;
	InitTimer5();
	delay20();
	delay1s();
		P1_1=1;
	InitTimer20();
	delay20();
	delay1s();
	P1_3=1;
	InitTimer5();
	delay20();
	delay1s();
	P1_4=1;
	InitTimer15();
	delay20();
	delay1s();
}
void init3()
{
	P1_2=1;
	InitTimer1();
	delay20();
	delay1s();
	P1_2=1;
	InitTimer15();
	delay20();
	delay1s();
	P1_0=1;
	InitTimer5();
	delay20();
	delay1s();
}
void main()
{
	TMOD=0x00;
	EA=1;
	EX0=1;
	init();
	while(1)
	{
	Init_Lcd();
	LCD_write_data('1');
	init2();
	init();
	delay1s();						 
	left();
	delay5();
	init3();
	right();
	delay1s();
	init2();
	}
}
void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x0FA;
    TL0 = 0x9A;
    init();
	TR0=0;
}

