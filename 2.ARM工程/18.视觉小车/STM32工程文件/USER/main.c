/*
 * @Author: your name
 * @Date: 2022-03-26 09:08:22
 * @LastEditTime: 2022-06-28 16:45:51
 * @LastEditors: MrLZR
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\main.c
 */
#include "main.h"
#include <cstring>
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
void To_forward()
{
  forward();
  delay_ms(1000);
  delay_ms(1000);
  delay_ms(1000);
  Turn_left();
  // delay_ms(350);
  delay_ms(100);
  // stop();
  // delay_ms(2000);
  forward();
  delay_ms(1000);
  delay_ms(1000);
  delay_ms(500);

  Turn_right();
  stop();
  delay_ms(1000);
}
void Step_1()
{
  while (PCin(15))
  {
    act();
    test();
    PCout(13) = 1;
  }
  PCout(13) = 0;
  stop();
  delay_ms(1000);
}
void Step_1_to_2()
{
  back();
  Turn_left();
  // delay_ms(200);
  // Turn_right()
  // back();
  stop();
  delay_ms(1000);
}
void Step_2()
{
  while (PCin(15))
  {
    act();
    test();
    PCout(13) = 1;
  }
  PCout(13) = 0;
  stop();
}

int main(void)
{
  Stm32_Clock_Init(9);
  delay_init(72);
  Car_PWM_Init();
  Encoder_Init_TIM2();
  Encoder_Init_TIM3();
  Encoder_Start();
  MyUSART_Init();
  LZR_GPIO_IN(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_15, GPIO_Speed_50MHz);
  LZR_GPIO_OUT(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_13, GPIO_Speed_50MHz);
  /**运行区********************************************************************************************************/
  stop();
  delay_ms(1000);
  // To_forward();
  forward();
  // /*****************************************************/
  delay_ms(500);
  stop();
  delay_ms(1000);
  Step_1();
  Step_1_to_2();
  forward();

  Step_2();
  back();
  stop();
  /**测试区********************************************************************************************************/
//  To_forward();
//   while (1)
//    ;

  //	while(1)
  //		;
}
