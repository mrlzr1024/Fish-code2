	#include "stm32f10x.h"
	#include "LED.h"
	#include "delay.h"
	#include "KEY.h"
	int main(){
	delay_init(64);
	LED_Init();
//	KEY_Init();
	while(1){
//	GPIO_SetBits(GPIOC,GPIO_Pin_13);//C13����ߵ�ƽ
//	GPIO_SetBits(GPIOB,GPIO_Pin_12);//B12����ߵ�ƽ
//	delay_ms(500);		
//  if(KEY_once()){
//	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//C13����͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);//B12����͵�ƽ
		delay_ms(50);
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//B12����ߵ�ƽ
		delay_ms(50);
//	}
	}
}
	
