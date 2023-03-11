#include<reg51.h>
sbit M0=P1^0;
int T;
unsigned char i=0;
//int i=0;
void delay1(void)   //1s
{
    unsigned char a,b,c;
    for(c=13;c>0;c--)
        for(b=247;b>0;b--)
            for(a=142;a>0;a--);
}
void delay(void)   //20ms
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=222;b>0;b--)
            for(a=40;a>0;a--);
}

void move(char k){
  T=k;
  TMOD=0x01;
  EA=1;
  ET0=1;
  TH0=(65536-100)/256;
  TL0=(65536-100)%256;
  TR0=1;
//  while(i<=200)
//    ;
  delay();
  TR0=0;
  
}
void main(void){
  int u=5;
 move(u);
  delay1();
 
  }
void time0(void) interrupt 1{
  TH0=(65536-100)/256;//0.1ms
  TL0=(65536-100)%256;
  i++;
  if(i==T){// T/10 ms
  M0=1;
  }
  else if(i==T+1&&i<=200){
  M0=0;
  }
}
  