/*
 * @Author: your name
 * @Date: 2021-12-03 19:48:24
 * @LastEditTime: 2021-12-12 21:45:04
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "stm32f10x.h"
#include "delay.h"
#include "GPIOBInit.h"
#include "sys.h"
#include "usart.h"

uint8_t Time;
uint8_t IrValue[6]; //[0]=地址码；[1]=地址反码；[2]=控制码；[3]=控制反码
void delay0(uint16_t i)
{
	delay_us(i*10);
}
void EXTIInit(void)
{
	InitGPIO(GPIOA, GPIO_Mode_Out_PP, GPIO_Pin_1, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
	InitGPIO(GPIOD, GPIO_Mode_IN_FLOATING, GPIO_Pin_0, RCC_APB2Periph_GPIOD, GPIO_Speed_50MHz);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	Ex_NVIC_Config(GPIO_D, 0, 1); //	Ex_NVIC_Config()
	MY_NVIC_Init(2, 0, EXTI0_IRQn, 2);
}
void EXTI0_IRQHandler(void)
{
	/*if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == 0) //确认是否真的接收到正确的信号
	{
		delay_ms(2);
		if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) == 0)
		{
			PAout(1) = !PAout(1);
		}
	}
	*/
	uint8_t j, k;
	uint16_t err;
	Time = 0;
	delay0(700);   // 7ms
	if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 0) //确认是否真的接收到正确的信号
	{

		err = 1000; // 1000*10us=10ms,超过说明接收到错误的信号
		/*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/
		while ((GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 0) && (err > 0)) //等待前面9ms的低电平过去
		{
			delay0(1);
			err--;
		}
		if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 1) //如果正确等到9ms低电平
		{
			err = 500;
			while ((GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 1) && (err > 0)) //等待4.5ms的起始高电平过去
			{
				delay0(1);
				err--;
			}
			for (k = 0; k < 4; k++) //共有4组数据
			{
				for (j = 0; j < 8; j++) //接收一组数据
				{

					err = 60;
					while ((GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 0) && (err > 0)) //等待信号前面的560us低电平过去
					{
						delay0(1);
						err--;
					}
					err = 500;
					while ((GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) == 1) && (err > 0)) //计算高电平的时间长度。
					{
						delay0(10); // 0.1ms
						Time++;
						err--;
						if (Time > 30)
						{
							return;
						}
					}
					IrValue[k] >>= 1; // k表示第几组数据
					if (Time >= 8)	  //如果高电平出现大于565us，那么是1
					{
						IrValue[k] |= 0x80;
					}
					Time = 0; //用完时间要重新赋值
				}
			}
		}
		if (IrValue[2] != ~IrValue[3])
		{
			return;
		}
	}
	PAout(1) =! PAout(1) ;
	EXTI_ClearITPendingBit(EXTI_Line0);
	if( IrValue[2]!=0x00){
	USART_SendData(USART1, IrValue[2]);
		}
	IrValue[2]=0x00;
}
void USART(void)
{
	uart_init(72,115200);	
	printf("OK?");
}
int main(void)
{  
	Stm32_Clock_Init(9);
	delay_init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	InitGPIO(GPIOA, GPIO_Mode_Out_PP, GPIO_Pin_0, RCC_APB2Periph_GPIOA, GPIO_Speed_50MHz);
	USART();
	EXTIInit();
	PAout(1) = 1;
	while (1)
	{
		if (IrValue[2] % 2 == 1)
		{
			PAout(0) = 1;
		}
		else if (IrValue[2] % 2 == 0)
		{
			PAout(0) = 0;
		}
//		printf("OK?");
	}
}


