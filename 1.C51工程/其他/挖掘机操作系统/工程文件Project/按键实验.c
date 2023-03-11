#include<reg52.h>
#include<KEY.h>
void delay10ms(void)   //ÑÓÊ±10ms
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

int KEY(void){
    if(KEY0==0){
      delay10ms();
      if(KEY0==0&&count==0){
        count++;
        return 1;
      }
    }
      count=0;
      return 0;
    }


