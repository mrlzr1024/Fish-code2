#include "My_GPIO.H"
uint16_t LZR_PIN[] = {
	GPIO_Pin_0,
	GPIO_Pin_1,
	GPIO_Pin_2,
	GPIO_Pin_3,
	GPIO_Pin_4,
	GPIO_Pin_5,
	GPIO_Pin_6,
	GPIO_Pin_7,
	GPIO_Pin_8,
	GPIO_Pin_9,
	GPIO_Pin_10,
	GPIO_Pin_11,
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15,
	GPIO_Pin_All};
void LZR_GPIO_OUT(uint32_t RCC_X, GPIO_TypeDef *GPIOX, uint16_t pin, GPIOSpeed_TypeDef frequency)
{
	GPIO_InitTypeDef GPIO_X;
	RCC_APB2PeriphClockCmd(RCC_X, ENABLE);
	GPIO_X.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_X.GPIO_Pin = pin;
	GPIO_X.GPIO_Speed = frequency;
	GPIO_Init(GPIOX, &GPIO_X);
}

void LZR_GPIO_IN(uint32_t RCC_X, GPIO_TypeDef *GPIOX, uint16_t pin, GPIOSpeed_TypeDef frequency)
{
	GPIO_InitTypeDef GPIO_X;
	RCC_APB2PeriphClockCmd(RCC_X, ENABLE);
	GPIO_X.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_X.GPIO_Pin = pin;
	GPIO_X.GPIO_Speed = frequency;
	GPIO_Init(GPIOX, &GPIO_X);
}
