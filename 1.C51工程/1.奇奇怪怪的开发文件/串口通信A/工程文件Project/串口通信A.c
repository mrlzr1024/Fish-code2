/*
 * @Author: your name
 * @Date: 2021-11-05 18:51:53
 * @LastEditTime: 2021-11-05 18:57:33
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \����ͨ��A1\src\main.c
 */
#include<reg52.h>
unsigned char dio(void){//MCU��
    unsigned char dat;
    while(RI==0)
      ;
    RI=0;
    dat=SBUF;
    return dat;
}

unsigned char send(void){//MCU��
  unsigned char j;
  TMOD=0x20;
  SCON=0x50;
  PCON=0x00;//������=9600
  TH1=0xfd;
  TL1=TH0;
  TR1=1;
  REN=1;
  j=dio();
  P1=j;
  return j;
}
void read(unsigned char back){//MUC��
  TMOD=0x20;
  SCON=0x40;
  PCON=0x00;//������=9600
  TH1=0xfd;
  TL1=TH0;
  TR1=1;
  //REN=1;
  SBUF=back;
}
void main(void){
  unsigned char y;
  while(1){
  y=send();
  read(y);
  }

}