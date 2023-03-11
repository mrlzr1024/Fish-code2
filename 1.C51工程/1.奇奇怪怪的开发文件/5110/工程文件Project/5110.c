#include<reg52.h>
#include"spi.h"
#include"CharCode.h"
#include"key.h"


 void delay(void)   //Îó²î -0.000000000045us
{
    unsigned char a,b,c;
    for(c=131;c>0;c--)
        for(b=156;b>0;b--)
            for(a=3;a>0;a--);
}




void main(void){
  int i=0;
  LCD_init();
  while(1){
    display(0,0,l0);
  }
}
