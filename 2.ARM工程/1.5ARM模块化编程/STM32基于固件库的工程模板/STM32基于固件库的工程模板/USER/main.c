#include"stm32f10x.h"
void Delay(u32 count)
{
	u32 i=10;
	for(;i<count;i++);
}
int main(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		//1便能PB, PE端口时钟L
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		//LED0-->PB.5 诺口記置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//I0日速 度为50MHz
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//初始化GPIOB.5_
		GPIO_SetBits(GPIOB,GPIO_Pin_All);
		//PB.5输出高
		GPIO_InitStructure. GPIO_Pin = GPIO_Pin_All;
		//LED1->PB.5推挽输出
//		GPIO_Init (GPIOE, &GPIO_InitStructure) ;
		//初始化GPIO
//		GPIO_SetBits(GPIOE,GPIO_Pin_All);
		//PE.5输出高
		while(1)
			{
		GPIO_ResetBits(GPIOB,GPIO_Pin_All);
//		GPIO_SetBits(GPIOE, GPIO_Pin_All);
		Delay(3000000);
		GPIO_SetBits(GPIOB,GPIO_Pin_All);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_All);
		Delay(3000000);
			} 
}


