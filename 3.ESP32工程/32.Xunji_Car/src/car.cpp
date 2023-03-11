#include "car.h"

int pin[] = {
    27, 26, 25, 33};
int channal_1 = 8, channal_2 = 9;

int pwm_1 = 15, pwm_2 = 12;

int port_1 = 5; //编码器1
int port_1_B = 18;

int port_2 = 19; //编码器2
int port_2_B = 4;
int max_power = 230;
void Car_init()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(pin[i], OUTPUT);
    }
    ledcSetup(channal_1, 1000, 8);   // 设置通道
    ledcSetup(channal_2, 1000, 8);   // 设置通道
    ledcAttachPin(pwm_1, channal_1); // 将通道与对应的引脚连接
    ledcAttachPin(pwm_2, channal_2); // 将通道与对应的引脚连接
}
void Action(bool a, bool b, bool c, bool d)
{
    bool val[] = {
        a, b, c, d};
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(pin[i], val[i]);
    }
}
void pwm_write(int pwm, int pwm2)
{
    pwm=pwm<0?0:pwm;
    pwm2=pwm2<0?0:pwm2;
    
    ledcWrite(8, pwm);
    ledcWrite(9, pwm2);
}
/*================OUT===========================================================================================================*/
void output(float pidd,int direction,int dist)
{
    if(direction>0){
        Action(0, 1, 1, 0);
        pidd=100;
    }
    else if(direction<0){
        Action(1, 0, 0, 1);
        pidd=100;
    }
    else if (pidd > 0)
    {

        Action(0, 1, 0, 1);
    }
    else if (pidd < 0)
    {
        pidd = -pidd;
        Action(1, 0, 1, 0);
    }
    else
    {
        Action(0, 0, 0, 0);
    }
    if (abs(pidd)  + support_r <= 250&&abs(dist)<20)
    {
        pidd += pidd<0?-support_r:support_r;
    }
    // else
    //     pidd = 220;
    if (pidd >= max_power)
        pidd = max_power;
    pwm_write(pidd, pidd);
}
bool Accident(float angle)
{
    if (abs(angle) > 45) //摔了就不动了(摆)....
    {
        pwm_write(0, 0);
        return false;
    }
    else
    {
        return true;
    }
    return true;
}

/*================PID===========================================================================================================*/
float Proportion = 0.8; //
float Integral = 0;     // 1.5; /
float Derivative = 0;   //

int pid_ctrl(int Encoder, int Target)
{

    // static float Bias, PWM_out, Integral_bias, Last_bias;
    // Bias = Encoder-Target;		// 计算偏差
    // Integral_bias += Bias;		// 计算偏差的积分
    // // 位置式PID控制器公式
    // PWM_out = Position_Kp*Bias+Position_Ki* Integral_bias+ Position_KD*(Bias- Last_bias);
    // Last_bias = Bias;			// 保存上一次偏差
    // return PWM_out;				// 输出
    // u(k) = u(k-1) + Kp * (e(k)-e(k-1)) + Ki * Ts * (e(k)+e(k-1))/2 + Kd * (e(k)-2*e(k-1)+e(k-2))/Ts
    static int LastError; // Error[-1]
    static int PrevError; // Error[-2]
    int iError, Outpid;   //
    Serial.print(Encoder);
    Serial.print(",");
    iError = Target - Encoder;
    Outpid = (Proportion * iError)       // E[k]
             - (Integral * LastError)    // E[k-1]
             + (Derivative * PrevError); // E[k-2]
    PrevError = LastError;               //
    LastError = iError;
    return Outpid; //
}

//=编码器================================e=====n=========c=========o=======d==========e====================================//
/*
 * 电机1圈11个脉冲
 * 减速比为1：48
 * 所以轮子转1圈共48*11=528个脉冲
 */

void blink();
void blink2();
unsigned long tleft = 0, tright = 0; //脉冲计数
float left = 1, right = 1;           //速度
unsigned long ltime = 0, rtime = 0;

//===flag区================//
int direction_r = 1,direction_l = 1; //电机旋转方向
void encode_init()
{
    // 配置中断引脚
    pinMode(port_1, INPUT_PULLUP);
    pinMode(port_1_B, INPUT_PULLUP);
    pinMode(port_2, INPUT_PULLUP);
    pinMode(port_2_B, INPUT_PULLUP);
    pinMode(2, OUTPUT | INPUT);
    // 检测到引脚 26 下降沿，触发中断函数 blink
    attachInterrupt(port_1, blink, FALLING);
    attachInterrupt(port_2, blink2, FALLING);
    Serial.println("\nstart irq test");
}

float left_speed()
{
    float tmp = millis() - ltime; //间隔时间
    if (tmp < 5)
    {
        return left * direction_l;
    }
    left = tleft / tmp;
    tleft = 0;
    ltime = millis();
    return left * direction_l;
}
float right_speed()
{
    float tmp = millis() - rtime; //间隔时间
    if (tmp <= 5)
    {
        return right * direction_r;
    }
    right = tright / tmp;
    tright = 0;
    rtime = millis();
    return right * direction_r;
}

// 中断函数
void blink()
{
    tleft++;
    direction_l = (digitalRead(port_1_B) == 1 ? -1 : 1);
}

void blink2()
{
    tright++;

    direction_r = (digitalRead(port_2_B) == 1 ? 1 : -1);

    // digitalWrite(2, !digitalRead(2));
}
