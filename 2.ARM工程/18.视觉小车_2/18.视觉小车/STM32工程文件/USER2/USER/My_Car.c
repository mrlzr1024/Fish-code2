/*
 * @Descripttion: Project's name
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-13 19:50:34
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-13 20:14:01
 * 功  能：配置电机驱动
备  注：
    硬件连接

    TIM4-CH3-PB9  ----  PWMA(右电机)
        PB15  ----  A2
        PB14  ----  A1

    TIM4-CH4-PB8  ----  PWMB(左电机）
        PB13  ----  B1
        PB12  ----  B2

 */
#include "My_Car.h"

//***************************配置***************************//
void Car_PWM_Init(void)
{
    PWM_Init(3600, 1); // PWM频率初始化20KHz
    GPIO_Config();     //电机驱动IO配置
}
//***************************PWM频率及占空比初始化***************************//
//=====初始化PWM 20KHZ 高频可以防止电机低频时的尖叫声
// ARR= 3599 时频率为20Khz
// PB0控制PWMA--left motor，PB1控制PWMB--right motor。STBY直接拉高
// arr：自动重装寄存器，psc分频系数
// PWM的频率 = 72MHz/ARR/PCS 例如  20K = 72M/3600/1 =  20K
void PWM_Init(u32 arr, int psc)
{
    TIM_OCInitTypeDef TIM_OCInitSructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    //配置pwm输出端口
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //初始化定时器

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能定时器4

    TIM_TimeBaseStructure.TIM_Period = arr - 1;                 //自动重新装载寄存器周期的值澹ㄥ计数值澹)
    TIM_TimeBaseStructure.TIM_Prescaler = psc - 1;              //时钟分频系数
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //对外部时钟进行采样的时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //参数初始化

    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    //设置通道3 pwm参数
    TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitSructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitSructure.TIM_Pulse = 0;                        //占空比=
    TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High; //当定时器计数值小于CCR1_Val时为高电平
    TIM_OC3Init(TIM4, &TIM_OCInitSructure);                  //参数初始化
    TIM_OC3PolarityConfig(TIM4, TIM_OCPreload_Enable);       //开始输出pwm

    //设置通道4 pwm参数
    TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitSructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitSructure.TIM_Pulse = 0;                        //占空比=
    TIM_OCInitSructure.TIM_OCPolarity = TIM_OCPolarity_High; //当定时器计数值小于CCR1_Val时为高电平
    TIM_OC4Init(TIM4, &TIM_OCInitSructure);                  //参数初始化
    TIM_OC4PolarityConfig(TIM4, TIM_OCPreload_Enable);       //开始输出pwm

    TIM_ARRPreloadConfig(TIM4, ENABLE); //启动自动重装
    TIM_Cmd(TIM4, ENABLE);              //启动定时
}
//***************************占空比调节***************************//
//占空比 = TIMx_CCRx / TIMx_ARR
// moto_r：右轮电机，moto_l：左轮电机.   数值 0-3600
void PWM_Out(u16 moto_l, u16 moto_r)
{

    TIM_OCInitTypeDef TIM_OCInitSructure;

    TIM_OCInitSructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitSructure.TIM_OutputState = TIM_OutputState_Enable;
    // CH3 左电机
    TIM_OCInitSructure.TIM_Pulse = moto_l;             //占空比= ccr/3600
    TIM_OC3Init(TIM4, &TIM_OCInitSructure);            //参数初始化
    TIM_OC3PolarityConfig(TIM4, TIM_OCPreload_Enable); //开始输出pwm

    // CH4 右电机
    TIM_OCInitSructure.TIM_Pulse = moto_r;             //占空比= ccr /3600
    TIM_OC4Init(TIM4, &TIM_OCInitSructure);            //参数初始化
    TIM_OC4PolarityConfig(TIM4, TIM_OCPreload_Enable); //开始输出pwm

    TIM_ARRPreloadConfig(TIM4, ENABLE); //启动自动重装
}
//**************************初始化PB12-15*****************************//
void GPIO_Config(void)
{
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                /*开启GPIO的外设时钟*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                     /*设置引脚模式为通用推挽输出*/
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                    /*设置引脚速率为50MHz */
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                               /*调用库函数，初始化GPIO*/
}
