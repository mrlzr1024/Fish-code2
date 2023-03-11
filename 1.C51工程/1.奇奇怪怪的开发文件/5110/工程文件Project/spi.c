#include"spi.h"
#include<reg52.h>
int font6x8[][6]={ 0x04,0x1C,0x3E,0x3E,0x1C,0x04 };
int blank[][6]={0x00,0x00,0x00,0x00,0x00,0x00};
void delay_1us(void){
}
/***********************************************************

�������ƣ�LCD_write_byte

�������ܣ�ģ��SPI�ӿ�ʱ��д����/����LCD

��ڲ�����data    ��д������ݣ�

          command ��д����/����ѡ��

���ڲ�������

�� ע��

***********************************************************/
void LCD_write_byte(unsigned char dat, unsigned char command){
  

    unsigned char i;

    LCD_CE = 0;                              //5110Ƭѡ��Ч��������������

    if (command == 0)                        //д����

         LCD_DC = 0;                         

    else  LCD_DC = 1;                    //д����

      for(i=0;i<8;i++)                            //����8bit����

            {

if(dat&0x80)

                        SDIN = 1;

                  else

                        SDIN = 0;

                  SCLK = 0;

                  dat = dat << 1;

                  SCLK = 1;

}

     LCD_CE = 1;                                //��ֹ5110

  }
/***********************************************************

�������ƣ�LCD_clear

�������ܣ�����Nakia5110

��ڲ�������

���ڲ�������

�� ע��

***********************************************************/
void LCD_clear(void){
    unsigned int i;

    LCD_write_byte(0x0c, 0);//��ͨ��ʾģʽ			
    LCD_write_byte(0x80, 0);//x��ʼ����		

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);			
  }

  /***********************************************************

�������ƣ�LCD_init

�������ܣ�5110��ʼ��

��ڲ�������

���ڲ�������

�� ע��

***********************************************************/

void LCD_init(void){

    LCD_RST = 0;     // ����һ����LCD��λ�ĵ͵�ƽ����

    delay_1us();

    LCD_RST = 1;

    LCD_CE = 0;     // �ر�LCD

    delay_1us();

    LCD_CE = 1;     // ʹ��LCD

    delay_1us();

    LCD_write_byte(0x21, 0);      // ʹ����չ��������LCDģʽ

    LCD_write_byte(0xBD, 0);      // ����Һ��ƫ�õ�ѹ���Աȶȵ���

    LCD_write_byte(0x06, 0);      // �¶�У��

    LCD_write_byte(0x13, 0);      // 1:48

    LCD_write_byte(0x20, 0);      // ʹ�û������V=0��ˮƽѰַ

    LCD_clear();                 // ����

    LCD_write_byte(0x0c, 0);      // �趨��ʾģʽ��������ʾ

    LCD_CE = 0;      // �ر�LCD
}
  
/***********************************************************

�������ƣ�LCD_set_XY

�������ܣ�����LCD��ʼ���꺯��

��ڲ�����X       ��0��83

          Y       ��0��5

���ڲ�������

�� ע��

***********************************************************/
void LCD_set_XY(unsigned char X, unsigned char Y){
  
   LCD_write_byte(0x40 | Y, 0);              // ��

   LCD_write_byte(0x80 | X, 0);        // ��

  }
/***********************************************************

�������ƣ�LCD_write_char

�������ܣ���ʾӢ���ַ�

��ڲ�����c      :  ��ʾ���ַ�

���ڲ�������

�� ע��

***********************************************************/
void LCD_write_char(int h[][6]){

    unsigned char line;

//    c -= 32;                       //������к�

    for (line=0; line<6; line++)

        LCD_write_byte(h[0][line], 1);

}

void LCD_draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map, unsigned char Pix_x,unsigned char Pix_y){
    unsigned int i,n;
    unsigned char row;//����λͼ��ռ����
      if (Pix_y%8==0)             //���Ϊλͼ��ռ����Ϊ����
           row=Pix_y/8;     
      else
         row=Pix_y/8+1;            //���Ϊλͼ��ռ������������
      LCD_set_XY(X,Y);
    for (n=0;n<row;n++)            //����
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