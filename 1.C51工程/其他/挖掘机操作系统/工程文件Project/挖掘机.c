#include<reg52.h>
#include"PCA9685.h"
sbit A=P2^1;
#define uchar unsigned char 
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
sbit KEY0=P2^4;
sbit KEY1=P2^5;
sbit KEY2=P2^6;
int count=0;
void delay10ms(void){
    unsigned char a,b;
    for(b=249;b>0;b--)
        for(a=17;a>0;a--);
}

int KEYB(void){
  if(KEY2==0){
    delay10ms();
    delay10ms();
    delay10ms();
    delay10ms();
    delay10ms();
    if(KEY2==0&&count==0){
      count++;
      return 1;
      }
    }
    else{
    count=0;
    }
  return 0;
      }

int KEYA(void){
if(KEY1==0){
  delay10ms();
  if(KEY1==0&&count==0){
    count++;
    return 1;
    }
  }
  else{
  count=0;
  }
return 0;
    }
int KEY(void){
if(KEY0==0){
  delay10ms();
  if(KEY0==0&&count==0){
    count++;
    return 1;
    }
  }
else{
count=0;
}
return 0;
    }
void main(void){
  int i=0;
  int mod=0;
    init();
		begin();
		setPWMFreq(50);
  
  while(1){
    A=0;
    P0=table[mod];
    delayms(10);
    A=1;
    if(KEYB()){mod++;if(mod>=3){mod=0;}}
    
    if(KEY()){
      servo_control(mod,i);//num为管脚号
			delayms(10);
      i+=10;
      if(i>180){i=180;}}
    
    else if(KEYA()){
      servo_control(mod,i);//num为管脚号
			delayms(10);
      i-=10;
      if(i<0){i=0;}}
    }
  }
