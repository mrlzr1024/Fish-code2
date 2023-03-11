/*
 * @Descripttion: Project's name
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-13 19:50:34
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-28 18:44:21
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
int pid_out = 0;
void act_b(void);
void act_r(void);
void left_r(void);
void right_r(void);
#include "string.h"
int P = 0;

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
//**************************显示函数*******************************//
void Display(void)
{
    int c_l = Read_Encoder(2);
    int c_r = Read_Encoder(3);
    if (c_l < 10000)
    {
        c_l = 0;
    }
    else
    {
        c_l = 30000 - c_l;
    }
    if (c_r < 10000)
    {
        c_r = 0;
    }
    else
    {
        c_r = 30000 - c_r;
    }
    // printf("PID_L:%-10d\t", Moto_Left);   //打印输出
    // printf("PID_R:%-10d\t", Moto_Right);  //打印输出
    // printf("SetPWML:%-10d\t", 2500);      //打印输出
    // printf("SetPWMR:%-10d\t", 2500);      //打印输出
    printf("right:%-10d\t", c_r);   //打印输出
    printf("left:%-10d \r\n", c_l); //打印输出
}

void back(void)
{
    PBout(12) = 0;
    PBout(13) = 1;
    PBout(14) = 1;
    PBout(15) = 0;
    PWM_Out(2600, 2500);
    // for(int i=0;i<15;i++){
    // delay_ms(2000);
    // }
    delay_ms(1000);
    // delay_ms(1000);
    // delay(4000);
    stop();
    delay_ms(2000);
}
void Turn_right(void)
{
    PBout(12) = 0;
    PBout(13) = 1;
    PBout(14) = 0;
    PBout(15) = 1;
    PWM_Out(2200, 2200);
    delay_ms(650);
    // delay_ms(850);
}
// Turn_left
void Turn_left(void)
{
    PBout(12) = 1;
    PBout(13) = 0;
    PBout(14) = 1;
    PBout(15) = 0;
    PWM_Out(2250, 2200);

    // delay_ms(650);
    delay_ms(300);
        // delay_ms(350);

}
void forward(void)
{
    PWM_Out(2300, 2300);
    PBout(12) = 1;
    PBout(13) = 0;
    PBout(14) = 0;
    PBout(15) = 1;
    
}

void stop(void)
{
    PBout(12) = 0;
    PBout(13) = 0;
    PBout(14) = 0;
    PBout(15) = 0;
}

int isdigit(char c)
{
    if (c >= 48 && c <= 57)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int Atoi(unsigned char *str, int cont)
{
    /*
    功能:将字符串中的第cont个数字转为int型；
    参数:str//待提前字符串；
        cont//要提取的第几个数字(从0开始)；
    返回:提取后转化的数字；
    */
    char num[16];
    long int num_s = 0;
    int i = 0, j = 0;
    int con = 0;
    int Switch = 0;
    memset(num, 0, sizeof(num));
    while (str[i] != NULL)
    {
        if (isdigit(str[i]))
        {
            if (con == cont)
            {
                num[j++] = str[i];
            }
            /*con++;*/
            Switch = 1;
        }
        i++;
        if (Switch == 1 && !isdigit(str[i]))
        {
            con++;
            Switch = 0;
        }
    }
    j--;
    i = 0;
    while (num[i] > 0)
    {
        num_s += (num[i++] - 48) * pow(10, j);
        j--;
    }
    if (str[1] == '-')
    {
        num_s = -num_s;
    }
    return num_s;
}

int para_L, para_R; //增量PID
int Moto_Left = 0, Moto_Right = 0;
u16 Speed_L, Speed_R;
// extern float OutData[4];
int Current_l = 0;
int Current_r = 0;
int Encoder_L = 0;
int Encoder_R = 0;
void Turning(u16 Set_Left, u16 Set_Right)
{
    Moto_Right = Set_Right;
    Moto_Left = Set_Left;

    Encoder_L = abs(abs(Read_Encoder(2)) - 30000); //读取编码器，计算出变化量,负号是因为两个电机 相对位置180°
    Encoder_R = abs(abs(Read_Encoder(3)) - 30000);
    // Encoder_L = (Read_Encoder(2)) - 30000; //读取编码器，计算出变化量,负号是因为两个电机 相对位置180°
    // Encoder_R = (-(Read_Encoder(3) - 30000));




    para_L = PID_Calc_Left(Encoder_L, Set_Left);   //左电机，计数得到增量式PID的增量数值
    para_R = PID_Calc_Right(Encoder_R, Set_Right); //右电机，计数得到增量式PID的增量数值
    Moto_Left += para_L;
    Moto_Right += para_R;
    if (Moto_Left > 3500)
        Moto_Left = 3500; //限幅 防止烧毁电机
    else if (Moto_Left <= 100)
    {
        Moto_Left = 1000;
    }
    if (Moto_Right > 3500)
        Moto_Right = 3500; //限幅
    else if (Moto_Right <= 100)
    {
        Moto_Right = 1000;
    }
    TIM4->CCR4 = Moto_Left;  //更新pwm
    TIM4->CCR3 = Moto_Right; //更新pwm

    // printf("Target_left:%5d\t", Set_Left); //目标输出
    // // printf("Target_right:%5d\t", Set_Left); //目标输出

    // printf("PID_L:%-5d\t", Moto_Left); //打印输出
    // // printf("PID_R:%-5d\t", Moto_Right); //打印输出

    // printf("Current_left:%-5d \r\n", Encoder_L); //打印输出
    printf("%d,%d \r\n", Encoder_L, Encoder_R);
    // printf("right:%-5d \r\n", Encoder_R);   //打印输出
}
void test()
{
    Encoder_L = abs(abs(Read_Encoder(2)) - 30000); //读取编码器，计算出变化量,负号是因为两个电机 相对位置180°
    Encoder_R = abs(abs(Read_Encoder(3)) - 30000);
    printf("%d,%d \r\n", Encoder_L, Encoder_R);
    if(Encoder_L==0&&Encoder_R==0){
        forward_2();
        delay_ms(75);
        // stop();
        // delay_ms(75);
        act();
    }
}
int throttle = 0; // max=3600;
void detect()
{
    // while (input[0] != 'r')
    // {
    printf("find=%d \r\n", throttle);
    PWM_Out(2050, 2050);
    if (throttle == 0)
    {
        left_r();
        delay_ms(200);
        throttle = 1;
    }
    else if (throttle == 1)
    {
        right_r();
        delay_ms(200);
        throttle = 0;
    }
    stop();
    delay_ms(100);

    // }
}
void act(void)
{
    static int count_r = 0;

    if (input[0] == 'r')
    {
        PWM_Out(2100, 2100);
        act_r();
        // stop();
        // delay_ms(100);
        count_r++;
        // while (PCin(15) && count_r >= 5)
        // {
        //     if (input[0] == 'r')
        //     {
        //         act_r();
        //         input[0] = ' ';
        //     }
        //     // else
        //     // {
        //     //     detect();
        //     // }
        // }
        if (PCin(15) == 0)
        {
            count_r = 0;
        }
    }
    else if (input[0] == 'b')
    {
        PWM_Out(2200, 2200);
        act_b();
    }
    else
    {
        PBout(12) = 1;
        PBout(13) = 0;
        PBout(14) = 0;
        PBout(15) = 1;
        PWM_Out(2200, 2200);
    }

    // switch (input[0])
    // {
    // case 'b':
    //     PWM_Out(2200, 2200);
    //     act_b();
    //     break;
    // case 'r':
    //     PWM_Out(2100, 2100);
    //     act_r();
    //     break;
    // default:
    //     PBout(12) = 1;
    //     PBout(13) = 0;
    //     PBout(14) = 0;
    //     PBout(15) = 1;
    //     PWM_Out(2600, 2500);
    //     break;
    // }
}

void forward_2(void)
{
     PBout(12) = 1;
    PBout(13) = 0;
    PBout(14) = 0;
    PBout(15) = 1;
    PWM_Out(2200, 2200);
}
void left(void)
{
    // TIM4->CCR3 = 2200;//加速端
    // TIM4->CCR4 = 0;
    PBout(12) = 0;
    PBout(13) = 0;
    PBout(14) = 0;
    PBout(15) = 1;
}
void right(void)
{
    // TIM4->CCR3 = 0;
    // TIM4->CCR4 = 2200;//加速端
    PBout(12) = 0; // 1
    PBout(13) = 0;
    PBout(14) = 1; // 0
    PBout(15) = 0;
}
void left_r(void)
{
    // TIM4->CCR3 = 2200;//加速端
    // TIM4->CCR4 = 0;
    PBout(12) = 0;
    PBout(13) = 0;
    PBout(14) = 0;
    PBout(15) = 1;
}
void right_r(void)
{
    // TIM4->CCR3 = 0;
    // TIM4->CCR4 = 2200;//加速端
    PBout(12) = 0; // 1
    PBout(13) = 0;
    PBout(14) = 1; // 0
    PBout(15) = 0;
}
void act_b(void)
{
    int P = Atoi(input, 0);
    int th=2050;
    // printf("===>%d<===/r/n",P);
    printf("靶子=%d \r\n", P);
    if (P >= 30)
    {
        PWM_Out(th, th);
        // printf("b_left=%d \r\n", P);
        left();
    }
    else if (P <= -20)
    {
        PWM_Out(th, th);
        // printf("b_right=%d \r\n", P);
        right();
    }
    else
    {
        PWM_Out(2200, 2200);
        PBout(12) = 1;
        PBout(13) = 0;
        PBout(14) = 0;
        PBout(15) = 1;
    }
}
void act_r()
{
    // stop();
    // delay_ms(50);
    P = Atoi(input, 0);
    printf("靶心 = %d \r\n", P);
    PWM_Out(2100, 2100); // 320+2000
    if (P >= 30)
    {
        // printf("s_left=%d \r\n", P);
        left_r();
    }
    else if (P <= -30)
    {
        // printf("s_right=%d \r\n", P);
        right_r();
    }
    // stop();
    // while(1)
    // ;
    else if (P >= -30 && P <= 30)
    {
        PWM_Out(2100, 2100);
        PBout(12) = 1;
        PBout(13) = 0;
        PBout(14) = 0;
        PBout(15) = 1;
        // PWM_Out(2000, 2000);
    }
}
