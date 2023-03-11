#include"stm32f10x.h"
#include"delay.h"
#include"LED.h"
#include"KEY.h"
int main(){
	LED_Init();
	KEY_Init();
	delay_init(8);
	
	while(1){
		while(KEY_once())
					;
		/*==================*/
		GPIOB->ODR|=1<<0;
		delay_ms(250);
		while(KEY_once());
		GPIOB->ODR&=~(1<<0);
		/*==================*/
		GPIOB->ODR|=1<<5;
		delay_ms(250);
			while(KEY_once());
		GPIOB->ODR&=~(1<<5);
		/*==================*/
		GPIOB->ODR|=1<<6;//¿ªB.5
		delay_ms(250);
			while(KEY_once());
		GPIOB->ODR&=~(1<<6);//¹ØB.5		
		/*==================*/		
		GPIOB->ODR|=1<<7;
		delay_ms(250);
			while(KEY_once());
		GPIOB->ODR&=~(1<<7);
		/*==================*/	
		GPIOE->ODR|=1<<5;
		delay_ms(250);
	}
}

