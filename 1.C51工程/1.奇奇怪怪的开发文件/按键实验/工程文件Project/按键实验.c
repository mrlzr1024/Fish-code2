#include<reg52.h>

sbit KEY0=P2^4;

sbit P2_0=P2^3;

#define uchar unsigned char 

uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void delay10ms(void)   //ÑÓÊ±10ms
{
    unsigned char a,b,c;
  
    for(c=1;c>0;c--)
  
        for(b=38;b>0;b--)
  
            for(a=130;a>0;a--);
  
}

void main(void){
  
  int count=0;
  
  int i=0;
  
  while(1){
    P2_0=0;
        
    P0=table[i];
        
    delay10ms();
    
    P2_0=1;
    
    if(KEY0==0){
      
      delay10ms();
      
      if(KEY0==0&&count==0){        
        
        count++;
        
        i++;
      }
    }
    else{
      
      count=0;
      
    }
    
    if(i>=10){
      
      i=0;
      
    }
    
  }
  
}