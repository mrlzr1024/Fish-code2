#include "GPIOBInit.h"
void InitGPIO(GPIO_TypeDef *GPIOX,GPIOMode_TypeDef Iomode,uint16_t pin,uint32_t Ioclock,GPIOSpeed_TypeDef Iospeed)
{
	GPIO_InitTypeDef GPIOBX;
	RCC_APB2PeriphClockCmd(Ioclock,ENABLE);
	GPIOBX.GPIO_Mode = Iomode;
	GPIOBX.GPIO_Pin = pin;
	GPIOBX.GPIO_Speed = Iospeed;
	GPIO_Init(GPIOX, &GPIOBX); //GPIOB初始化
}

