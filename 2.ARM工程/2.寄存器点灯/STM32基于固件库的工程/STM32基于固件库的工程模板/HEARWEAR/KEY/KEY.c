#include"KEY.h"
#include"stm32f10x.h"
#include"sys.h"
#include"delay.h"
//#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
#define KEY1PRES 1;
void KEY_Init(void){
	GPIO_InitTypeDef GPIO_InitStucture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能时钟
	GPIO_InitStucture.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStucture.GPIO_Mode=GPIO_Mode_IPU;//下拉输入
	GPIO_Init(GPIOA,&GPIO_InitStucture);
}
int KEY_Alot(void){
	uint8_t KEY1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	if(KEY1==0){
		delay_ms(30);
		if(KEY1==0){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}
int KEY_once(void){
	uint8_t KEY1=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	static int tmp=0;
	if(KEY1==0){
		delay_ms(10);
		if(KEY1==0&&tmp==0){
			tmp++;
			return 1;
		}
	}
	else if(KEY1==1){
	tmp=0;
	return 0;
	}
	return 0;
}
	
	


