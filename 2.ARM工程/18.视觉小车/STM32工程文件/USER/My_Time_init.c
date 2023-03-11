/*
 * @Descripttion: your project
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-13 19:12:00
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-26 15:47:53
 */
#include "My_Time_init.h"


void NVIC_Config(void);
void NVIC_TIM1_Config(void);

//***************************定时器2初始化 ，使用编码器功能***************************//
//左电机编码器计数
// PA15----接 编码器A相 或者电机驱动的B1A标识
// PB3 ----接 编码器B相 或者电机驱动的B1B标识
void Encoder_Init_TIM2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    // GPIO功能时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //禁用JTAG
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);        //全映射

    //配置IO口为复用功能-定时器通道
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //速度100MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // TIM时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // Timer configuration in Encoder mode
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

    // Reset counter
    TIM2->CNT = 0;

    TIM_Cmd(TIM2, ENABLE);
}

//***************************定时器3初始化 ，使用编码器功能***************************//
//左电机编码器计数
// PB4----接 编码器A相 或者电机驱动的B2A标识
// PB5----接 编码器B相 或者电机驱动的B2B标识
void Encoder_Init_TIM3(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    // GPIO功能时钟使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    //配置IO口为复用功能-定时器通道
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     //速度100MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // TIM时钟使能
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //这个就是重映射功能函数

    // Timer configuration in Encoder mode
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling
    TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 0;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // Reset counter
    TIM_SetCounter(TIM3, 0);

    TIM_Cmd(TIM3, ENABLE);
}

/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回值：速度值
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;
    switch (TIMX)
    {
    case 2:
        Encoder_TIM = (short)TIM2->CNT;
        TIM2->CNT = 30000;
        break;
    case 3:
        Encoder_TIM = (short)TIM3->CNT;
        TIM3->CNT = 30000;
        break;
        // case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=30000;break;
        // case 5:  Encoder_TIM= (short)TIM5 -> CNT;  TIM5 -> CNT=30000;break;
    default:
        Encoder_TIM = 0;
    }
    return Encoder_TIM;
}

//***************************定时器初始化 ，使用编码器功能***************************//
void Encoder_Start(void)
{
    TIM2->CNT = 30000;
    TIM3->CNT = 30000;
}

// /********PID定时器************************/
// void Timer1_Init(void)
// {
//     NVIC_Config();
//     TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

//     TIM_TimeBaseStructure.TIM_Period = 99;                     //自动重新装载寄存器周期的值澹ㄥ计数值澹)//999-10ms;499-5ms
//     TIM_TimeBaseStructure.TIM_Prescaler = 719;                  //时钟分频系数
//     TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //对外部时钟进行采样的时钟分频
//     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
//     TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //高级定时器1是用定时器功能配置这个才可以是正常的计数频率一开始的72mhz 值得注意的地方
//     TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);             //参数初始化

//     TIM_ClearFlag(TIM1, TIM_FLAG_Update);
//     TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

//     TIM_Cmd(TIM1, ENABLE); //启动定时器

// }
// void NVIC_Config(void)
// {
//     NVIC_TIM1_Config();
// }

// void NVIC_TIM1_Config(void)
// {
//     NVIC_InitTypeDef NVIC_InitStructure;

//     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//     NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_Init(&NVIC_InitStructure);
// }

// void TIM1_UP_IRQHandler(void)
// {
//     if (TIM_GetFlagStatus(TIM1, TIM_IT_Update) != RESET) //时间到了
//     {
//         TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //清中断
//           printf("%d \r\n", Encoder_L);
//         //Turning(2500, 2500);
//     }
// }
