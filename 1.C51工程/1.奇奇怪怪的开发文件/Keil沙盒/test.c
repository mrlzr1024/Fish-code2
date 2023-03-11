#include<reg51.h>
#include<stdio.h>
sbit RS=P2^3;
sbit RW=P2^4;
sbit EN=P2^5;
sbit A=P2^0;
sbit C=P2^1;
void delay10(void){//10msÑÓÊ±
    unsigned char a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}

void delay(void){//0.5s
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}

void delay5(void){//5ms
    unsigned char a,b;
    for(b=19;b>0;b--)
        for(a=130;a>0;a--);
}
void delay15(void){//15ms
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=238;b>0;b--)
            for(a=30;a>0;a--);
}
void Read(){//read the sate
	RS=0;
	RW=1;
	EN=1;
	delay15();
}
void command(int com){
	RS=0;
	RW=0;
	P0=com;
	delay5();
	EN=1;
	delay5();
	EN=0;
}
void Read2(){//Read the Date
	RS=1;
	RW=1;
	EN=1;
	delay15();
}
void Write(char txt){
	RS=1;
	RW=0;
	P0=txt;
	delay5();
	EN=1;
	delay5();
	EN=0;
}
void init(){//init the LCD
	RS=0;
	RW=0;
	EN=0;
	Read();
	command(0x38);
	command(0x0c);
	command(0x06);
	command(0x80);
	delay5();
	Read2();	
}


void main(void){
	int i;
	init();
	for(i=0;i<=40;i++){
	char a;
	A=1;
	C=1;
	delay10();
	a=i+'0';
	Write(a);
	delay5();
	delay();
	command(0x80+i*3);
	command(0x07);
	RS=1;
	}
	while(1);
}