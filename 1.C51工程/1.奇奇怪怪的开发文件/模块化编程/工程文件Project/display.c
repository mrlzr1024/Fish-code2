#include"main.h"
void delay(int z)
{
	uint x,y;
	for(x=z;x>0;x--);
		for(y=110;y>0;y--);
}
void write_com(uint COM)
{
	RS=0;
	RW=0;
	P0=COM;
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
	write_com(0x80+54);
}
