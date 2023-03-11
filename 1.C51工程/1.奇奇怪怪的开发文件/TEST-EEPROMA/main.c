#include <reg52.h>
#include "at24c02.h"
//#include "uart.h"
void  MCUBinit(void){
  TMOD=0X20;
  SCON=0X40;
  
  PCON=0x00;
  TH1=0Xfd;
  TR1=1;
}
void MCUBack(unsigned char k){
  MCUBinit();
  SBUF=k;
}



void delay20ms(void)   //��� -0.000000000005us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=222;b>0;b--)
            for(a=40;a>0;a--);
}

/*******************************************************************************
* �� �� ��         : main
* ��������         : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void main()
{
  int x=0;
    unsigned char i;
    unsigned char addr; 
    unsigned char src_data[] = "()ab#cde!fg1234567";    
    unsigned char buf[8] = "ABCDEFGH";
    //MCUBinit();
/*
    for (i=0; i<128; i++)
    {
        uart_send_byte(i);
    }
    while (1);
*/
    // �������һ�����ݣ�Ʃ��"abcdefg1234567-_-*&%@/\"
    // ����Щд��EEPROM���ض���ַ��
    // Ȼ���EEROM����Щ��ַ��������ͨ�����ڴ�ӡ�������ǲ�������д���
  for(x=0;x<20;x++){
    MCUBack('T');
    delay20ms();
    MCUBack('%');
      delay20ms();
  }

    addr = 4;
    for (i=0; i<8; i++)
    {
        At24c02Write(addr, src_data[i]);
        delay20ms();
      MCUBack('o');
      delay20ms();
        addr++;
    }

    for (i=0; i<8; i++)
    {
        MCUBack(buf[i]);
      delay20ms();
      
    }


    for (i=0; i<20; i++)
    {
        MCUBack('-');
      delay20ms();
    }

    // ��������
    addr = 4;
    for (i=0; i<8; i++)
    {
        buf[i] = At24c02Read(addr);
        delay20ms();
        addr++;
    }

    for (i=0; i<8; i++)
    {
      MCUBack('*');
      delay20ms();
        MCUBack(buf[i]);
      delay20ms();
    }
MCUBack('|');
      delay20ms();
    while (1);

    // ��һ������
    // ��д��һЩ�ض����ݣ�Ȼ��ػ��ϵ磻Ȼ��Ĵ���Ϊ��������ӡ��ʾ������

}           