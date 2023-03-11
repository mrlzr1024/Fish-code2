#include<reg51.h>
void delay(void)
{
 unsigned char i,j;
  for(i=0;i<50;i++)
    for(j=0;j<50;j++)
	;
}
void main(void)
{
   while(1)
   { 
   P3=0xfe;
   delay();
   P3=0xfd;
   delay();
   P3=0xfb;
   delay();
   }
}
   

