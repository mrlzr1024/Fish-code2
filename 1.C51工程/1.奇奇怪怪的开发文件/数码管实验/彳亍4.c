#include<reg52.h>
#define uchar unsigned char 
sbit wela=P2^0;
sbit dula=P2^1;
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
	}
void main()
{
 P0=0xfe;
 wela=0;
 delay(5);
 wela=1;
{
    unsigned int  a;
   
 while(1)
 {
 
   for(a=100;a>0;a--)
   {
     display();
   }
 
 }
}
}