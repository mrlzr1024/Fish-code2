#include<reg51.h>
#define uchar unsigned char
sbit S=P2^0;
sbit H=P2^1;
sbit TEN=P2^2;
sbit O=P2^3;
int C;
char T;
char E; 
void delay(uchar i)
{
  uchar j,k; 
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
	}    	
uchar code table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
void main()
{
	C=9999;
	while(1)
	{
		E=C%10;
		P0=table[E]; //¸öÎ»
		O=0;
		delay(2);
		O=1;
	}	
}
