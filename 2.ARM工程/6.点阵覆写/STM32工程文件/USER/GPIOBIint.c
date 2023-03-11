#include "GPIOBInit.h"
void InitGPIO(int pin,int frequency,GPIO_TypeDef *GPIOX)
{
	GPIO_InitTypeDef GPIOBX;
	GPIOBX.GPIO_Mode = GPIO_Mode_Out_PP;
	switch (pin)
	{
	case 0:
		GPIOBX.GPIO_Pin = GPIO_Pin_0; //B0
		break;
	case 1:
		GPIOBX.GPIO_Pin = GPIO_Pin_1; //B0
		break;
	case 2:
		GPIOBX.GPIO_Pin = GPIO_Pin_2; //B0
		break;
	case 3:
		GPIOBX.GPIO_Pin = GPIO_Pin_3; //B0
		break;
	case 4:
		GPIOBX.GPIO_Pin = GPIO_Pin_4; //B0
		break;
	case 5:
		GPIOBX.GPIO_Pin = GPIO_Pin_5; //B0
		break;
	case 6:
		GPIOBX.GPIO_Pin = GPIO_Pin_6; //B0
		break;
	case 7:
		GPIOBX.GPIO_Pin = GPIO_Pin_7; //B0
		break;
	case 8:
		GPIOBX.GPIO_Pin = GPIO_Pin_8; //B0
		break;
	case 9:
		GPIOBX.GPIO_Pin = GPIO_Pin_9; //B0
		break;
	case 10:
		GPIOBX.GPIO_Pin = GPIO_Pin_10; //B0
		break;
	case 11:
		GPIOBX.GPIO_Pin = GPIO_Pin_11; //B0
		break;
	case 12:
		GPIOBX.GPIO_Pin = GPIO_Pin_12; //B0
		break;
	case 13:
		GPIOBX.GPIO_Pin = GPIO_Pin_13; //B0
		break;
	case 14:
		GPIOBX.GPIO_Pin = GPIO_Pin_14; //B0
		break;
	case 15:
		GPIOBX.GPIO_Pin = GPIO_Pin_15; //B0
		break;
	default:
		break;		
	}
	switch (frequency){
		case 50:
			GPIOBX.GPIO_Speed = GPIO_Speed_50MHz;
			break;
		case 2:
			GPIOBX.GPIO_Speed = GPIO_Speed_2MHz;
			break;
		case 10:
			GPIOBX.GPIO_Speed = GPIO_Speed_10MHz;
			break;
		default:
			break;

	}
	GPIO_Init(GPIOX, &GPIOBX); //GPIOB初始化
}

