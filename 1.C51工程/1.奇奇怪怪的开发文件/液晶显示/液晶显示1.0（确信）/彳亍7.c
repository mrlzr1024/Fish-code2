#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^3;
sbit RW=P2^4;
sbit EN=P2^5;
sbit A=P2^0;
sbit C=P2^1;
uchar com;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--);
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	RS=0;
	RW=0;
	P0=com;
	delay(5);
	EN=1;
	delay(5);
	EN=0;
}
void write_data(char date)
{
	RS=1;
	P0=date;
	delay(5);
	EN=1;
	delay(5);
	EN=0;
} 
void init()
{
	EN=0;
	write_com(0x38);
	write_com(0x0e);
	write_com(0x06);
	write_com(0x80);
}
void main()
{
	A=1;
	C=1;
	init();
	delay(6);
	write_data('A');
	delay(20);
	while(1);
}