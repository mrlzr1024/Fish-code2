#include <reg52.h>
#include "intrins.h"
#define uchar unsigned char
#define uint unsigned int 


//#define                        L1                0x80            // ��һ��д���ַ
//#define                        L2                0xc0            // �ڶ���д���ַ
        
sbit SCL = P2^0;
sbit SDA = P2^1;


//char ADDR = 0x4E;    // PCF8574  T  ģ��ĵ�ַ��
char ADDR = 0x7e;    // PCF8574   AT  ģ��ĵ�ַ��


//***************************** ��ʱ y  ms ***********************************************


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






//******************************** IIC ���ڿ�ʼ ********************************************


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




//********************************** IIC ����д1���ֽ� ******************************************


void IIC_writeByte(char temp)
{
        char i;
        for(i=0;i<8;i++)
        {
                SDA=(bit)(temp & 0x80) ;   // ���ݹ涨1602���������λ����Ϊ  1  
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




//******************************** 1602д���� ********************************************


void LCD_write_command(char comm)
{
        char tmp;
        IIC_start();          // ���ڿ�ʼ
        IIC_writeByte(ADDR);  // ��ѡPCF 8574T �ĵ�ַ  ��Ӧ�����൱��ѡ�е���˼�ɣ�
        
        tmp = comm & 0xF0;    // ��0xf0 Ӧ����ȡ����λ����˼��
        tmp |= 0x0C;         //������4λΪָ��ĸ���λ������λΪ   RS = 0, RW = 0, EN = 1  
        IIC_writeByte(tmp);  //�Ӵ����ͳ�
        delay1(20);
        tmp &= 0xFB;        //Make EN = 0
        IIC_writeByte(tmp); 
        
        tmp = (comm & 0x0F) << 4 ;  //��ָ��ĵ���λ �͵���λ�ñ���
        tmp |= 0x0C;        //RS = 0, RW = 0, EN = 1
        IIC_writeByte(tmp);
        delay1(20);
        tmp &= 0xFB; // Make EN = 0
        IIC_writeByte(tmp);
        
}
//******************************** 1602д���� ********************************************


void LCD_write_data(char data1)
{
        char tmp;
        IIC_start();
        IIC_writeByte(ADDR);   // ��ѡPCF 8574T �ĵ�ַ  ��Ӧ�����൱��ѡ�е���˼�ɣ�
        
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


//******************************** 1602��ʼ�� ********************************************


void Init_Lcd(void)
{
        LCD_write_command(0x33); //��8λ����תΪ4λ����
        delay1(50) ;
        LCD_write_command(0x32); //
        delay1(50) ; 
        LCD_write_command(0x28); // 4λ�����ߣ���ʾ2�У�5*7�����ַ�  �������0x38  ��Ϊ8λ�����ߣ���ʾ2�У�5*7�����ַ�
        delay1(50) ; 
        LCD_write_command(0x0C); // ����ʾ���رչ�꣬����˸
        delay1(50) ;  
        LCD_write_command(0x06); // �趨���뷽ʽ��������λ��
        delay1(50) ; 
        LCD_write_command(0x01); // ����
        delay1(50) ;
}








//*************************************** ��ָ��λ����ʾ�ַ��� *************************************


void Write_LCD(int x, int y, char *str)
{
        char addr;
        if( x < 0)
        {
                x = 0;
        }
        if(x > 15)
        {
                x = 15;
        }
        if(y<0)
        {
                y = 0;
        }
        if(y > 1)
        {
                y = 1;
        }
        
        addr = 0x80 + 0x40 * y + x;   // Move cursor  �ƶ����
        LCD_write_command(addr);
        while (*str) 
        {
                LCD_write_data(*str++); 
        }
}


//-------------------------------------------- ��ʾ�ַ����ĺ��� ----------------------------------------------------


void LCD_write_word(unsigned char *s)                  //��ʾ�ַ����ĺ���
{
        while(*s>0)
        {
                LCD_write_data(*s);
                s++;
        }
}




//********************************* ָ��λ����ʾһ���ַ�*******************************************


/*
void Print_Char (unsigned char line,unsigned char num,unsigned char date)
{
                LCD_write_command(line+num);
                LCD_write_data(date);
}


*/




//��ָ��λ����ʾһ���ַ�(���1602Һ��)-�����¶���ʾ


void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
Y &= 0x1;
X &= 0xF;                 //����X���ܴ���15��Y���ܴ���1
if (Y) X |= 0x40;        //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
X |= 0x80;               // ���ָ����
LCD_write_command(X);    //���ﲻ���æ�źţ����͵�ַ��
LCD_write_data(DData);
}

void main(){
	Init_Lcd();
	DisplayOneChar(4,1,'T');
	while(1);

}