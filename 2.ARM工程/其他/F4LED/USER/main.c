/*
 * @Author: your name
 * @Date: 2021-12-28 07:11:15
 * @LastEditTime: 2021-12-31 09:11:36
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
																																											//#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "main.h"
void RCC_MyConfig(void)
{
    RCC_DeInit();                                                              //@1
    RCC_HSEConfig(RCC_HSE_ON);                                   //打开外部时钟
    
    if(RCC_WaitForHSEStartUp() == SUCCESS)                  //等待外部时钟成功启动
    {
 			
        RCC_HCLKConfig(RCC_SYSCLK_Div1);                          //HCLK（AHB）时钟为系统时钟1分频
        
        RCC_PCLK1Config(RCC_HCLK_Div8);                            //PCLK（APB1）时钟为HCLK时钟8分频
        RCC_PCLK2Config(RCC_HCLK_Div2);                            //PCLK（APB2）时钟为HCLK时钟2分频
  
        
        RCC_PLLConfig(RCC_PLLSource_HSE, 8, 288, 4, 6);     //PLL时钟配置，外部晶振为8MHz，系统配置为8/8*336/4 =84MHz usb=336/7=48
        
        RCC_PLLCmd(ENABLE);                                               //开启PLL时钟，并等待PLL时钟准备好
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);      //选择PLL时钟为系统时钟
       
        while(RCC_GetSYSCLKSource() != 0x08);                      //Wait till PLL is used as system clock source
    }
}
int main(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_MyConfig();
  delay_init(72);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  while(1){
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		delay_ms(500);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		delay_ms(500);
//		GPIOC->ODR=0X00;
	}
}
/**/


