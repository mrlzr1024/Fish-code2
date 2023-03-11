#include<reg51.h>
#include<ENGINE.h>

void delay100us(int k){//延时k*100us
  T=k;
  TMOD=0x02;
  EA=1;
  ET0=1;
  TH0=165;//100us要计92.16次
  TL0=TH0;
  TR0=1;
  while(T>0)
    ;
}
void move(int angle)//180度舵机控制程序
{
  int pwm=0;
  pwm=5+angle*20/180;
  M0=1;
  delay100us(pwm);
  M0=0;
  delay100us(200-pwm);
}
//void main(void){
//  int h=60;
//  int l=0;
//  M0=0;
//  while(1){
//    for(l=0;l<3;l++){
//   move(h);
//    }
//   h+=20;
////    move(h);
//    if(h>=180){
//      h=0;
//    }
//  }
//}

  