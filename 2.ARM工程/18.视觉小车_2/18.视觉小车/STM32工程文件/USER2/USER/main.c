/*
 * @Author: your name
 * @Date: 2022-03-26 09:08:22
 * @LastEditTime: 2022-06-15 15:12:05
 * @LastEditors: MrLZR
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "main.h"

//硬件链接说明
//电机控制pwm,用到了timer3的ch3和ch4，即 PB0-PB1连接电机驱动的使能端PWMA（左电机）和PWMB（右电机）
//电机正反控制：INA1和INA2控制 一路（左电机）
//	  				 INB1和INB2控制 一路（右电机）
//             PWMA ---- PB8
//             PWMB ---- PB9
//             INA2 ---- PB12
//             INA1 ---- PB13
//             INB1 ---- PB14
//             INB2 ---- PB15
//             PB0控制PWMA--left motor，PB1控制PWMB--right
//右电机编码器计数
//             PA15----接 编码器A相 或者电机驱动的B1A标识
//             PB3 ----接 编码器B相 或者电机驱动的B1B标识
//左电机编码器计数
//             PB4----接 编码器A相 或者电机驱动的B2A标识
//             PB5----接 编码器B相 或者电机驱动的B2B标识
int main(void)
{

    NVIC_InitTypeDef NVIC0;
    USART_InitTypeDef USART0;
		Stm32_Clock_Init(9);
		delay_init(72);
    Car_PWM_Init();
    Encoder_Init_TIM2();
    Encoder_Init_TIM3();
    Encoder_Start();
    My_Usart_Init(USART0,NVIC0);
    PWM_Out(2500, 2500);
		PBout(12)=1;
		PBout(13)=0;
		PBout(14)=0;
		PBout(15)=1;
    while(1){
			printf("left:%d \r\n",Read_Encoder(2));//打印输出
			printf("right:%d \r\n",Read_Encoder(3));//打印输出
        delay_ms(500);
    }
//	while(1)
//		;
}







