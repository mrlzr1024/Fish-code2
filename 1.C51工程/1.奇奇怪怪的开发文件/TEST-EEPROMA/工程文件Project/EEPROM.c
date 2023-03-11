#include<reg52.h>
#include"I2CA.h"
void delay(void)   //误差 -0.000000000001us
{
    unsigned char a,b;
    for(b=15;b>0;b--)
        for(a=152;a>0;a--);
}
//unsigned char dio(void){//MCU收
//    unsigned char dat;
//    while(RI==0)
//      ;
//    RI=0;
//    dat=SBUF;
//    return dat;
//}

//unsigned char send(void){//MCU收
//  unsigned char j;
//  TMOD=0x20;
//  SCON=0x50;
//  PCON=0x00;//波特率=9600
//  TH1=0xfd;
//  TL1=TH0;
//  TR1=1;
//  REN=1;
//  j=dio();
//  P1=j;
//  return j;
//}
//void read(unsigned char back){//MUC寄
//  TMOD=0x20;
//  SCON=0x40;
//  PCON=0x00;//波特率=9600
//  TH1=0xfd;
//  TL1=TH0;
//  TR1=1;
//  //REN=1;
//  SBUF=back;
//}
void  MCUBinit(void){
  TMOD=0X20;
  SCON=0X40;
  
  PCON=0x00;
  TH1=0Xfd;
  TR1=1;
}
void  MCUGinit(void){
  TMOD=0X20;
  SCON=0X50;
  
  PCON=0x00;
  TH1=0Xfd;
  TR1=1;
  REN=1;
}
unsigned char MCUGet(void){
  unsigned char j;
  MCUGinit();
  while(RI==0)
    ;
  RI=0;
  j=SBUF;
  return j;
}
void MCUBack(unsigned char k){
  MCUBinit();
  SBUF=k;
}
void main(void){
  unsigned char L=0;
  unsigned char K=0;
  while(1){
  L=MCUGet();
    P1=L;
  init();
  start();
  write_byte(0xa0);
  ACK();
  write_byte(L);//写0xfe
  ACK();
  stop();
  P1=L;
  delay();
  delay();
  
  start();
  write_byte(0xa0);
  ACK();
  K=read_byte();//写0xfe
    ACK();
  stop();
   MCUBack(K);
 P1=K;
  }
}