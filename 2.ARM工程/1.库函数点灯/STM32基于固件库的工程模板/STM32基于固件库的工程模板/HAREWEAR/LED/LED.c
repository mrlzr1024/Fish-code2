#include"LED.h"
#include"stm32f10x.h"


void LED_Init(void){
	GPIO_InitTypeDef GPIO_InitSr;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//GPIOA
	//GPIOB_12
	GPIO_InitSr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitSr.GPIO_Pin=GPIO_Pin_12;//B12
	GPIO_InitSr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitSr);//B
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//B12输出高电平
	//GPIOA_5
	GPIO_InitSr.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitSr.GPIO_Pin=GPIO_Pin_5;//A5
	GPIO_InitSr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitSr);//A5
	GPIO_SetBits(GPIOA,GPIO_Pin_5);//A5输出高电平
}
