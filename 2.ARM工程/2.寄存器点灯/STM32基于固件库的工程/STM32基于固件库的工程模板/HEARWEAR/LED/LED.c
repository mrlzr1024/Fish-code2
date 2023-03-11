#include"LED.h"
#include"stm32f10x.h"
void LED_Init(void){
	//初始化io口寄存器
	RCC->APB2ENR|=1<<3;//0....001000第三位寄存器（GPIOB），而不影响其他位
	RCC->APB2ENR|=1<<6;//0....100000第六位寄存器(GPPIOE)，而不影响其他位
	//GPIOB.5
	GPIOB->CRL&=0x000FFFF0;//位运算中&=1(与1运算)使除第3，4，5，6位外的位清零
	GPIOB->CRL|=0X33300003;
	GPIOB->ODR|=1<<0;//置高电平
	GPIOB->ODR|=1<<5;
	GPIOB->ODR|=1<<6;
	GPIOB->ODR|=1<<7;
	//GPIOE.5
	GPIOE->CRL&=0xff0fffff;//位运算中&=1(与1运算)使除第5位外的位清零
	GPIOE->CRL|=0X00300000;
	GPIOE->ODR|=1<<5;
}


