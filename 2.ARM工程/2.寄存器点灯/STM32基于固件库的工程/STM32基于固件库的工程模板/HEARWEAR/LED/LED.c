#include"LED.h"
#include"stm32f10x.h"
void LED_Init(void){
	//��ʼ��io�ڼĴ���
	RCC->APB2ENR|=1<<3;//0....001000����λ�Ĵ�����GPIOB��������Ӱ������λ
	RCC->APB2ENR|=1<<6;//0....100000����λ�Ĵ���(GPPIOE)������Ӱ������λ
	//GPIOB.5
	GPIOB->CRL&=0x000FFFF0;//λ������&=1(��1����)ʹ����3��4��5��6λ���λ����
	GPIOB->CRL|=0X33300003;
	GPIOB->ODR|=1<<0;//�øߵ�ƽ
	GPIOB->ODR|=1<<5;
	GPIOB->ODR|=1<<6;
	GPIOB->ODR|=1<<7;
	//GPIOE.5
	GPIOE->CRL&=0xff0fffff;//λ������&=1(��1����)ʹ����5λ���λ����
	GPIOE->CRL|=0X00300000;
	GPIOE->ODR|=1<<5;
}


