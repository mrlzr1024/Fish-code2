class PID_Contral
{
private:
    // float Balance_Kp = 8.9 * 0.6,        // 17 <25  l 6.9 //大幅度的低频抖动
    //     Balance_Kd = 0.3 * 0.6,          // 0.2,  //高频的剧烈抖动    zx
    //     Velocity_Kp = 100,              // 100, s105 l 85 k 86.8
    //     Velocity_Ki = Velocity_Kp / 200+0.2, //掌管路程m1.5 n2.2 s2.5
    //     Velocity_Ki_2 = 88 / 200,        //掌管路程m1.5 n2.2 s2.5
    //     Velocity_Kd = 0;
    float Balance_Kp = 8.9 * 0.6,        // 17 <25  l 6.9 //大幅度的低频抖动
        Balance_Kd = 0.3 * 0.6,          // 0.2,  //高频的剧烈抖动    zx
        Velocity_Kp = 88,              // 100, s105 l 85 k 86.8
        Velocity_Ki = Velocity_Kp / 200, //掌管路程m1.5 n2.2 s2.5
        //Velocity_Ki_2 = 88 / 200,        //掌管路程m1.5 n2.2 s2.5
        Velocity_Kd = 0;
    float dead_angle = 0;
    int max = 250, Velocity_max = 250;
    int push = 20, Velocity_push = 0;
    float Encoder_Integral_max = 100, Encoder_push = 0;
    

public:
    float Velocity, Encoder_Least, Encoder, Movement;
    float Encoder_Integral, Target_Velocity;
    int Flag_Left=0,Flag_Right=0;
    void change(float val)
    {
        Velocity_Kp = val;
    }
    float return_kp()
    {
        return Velocity_Kp;
    }
    /**************************************************************************
      函数功能：直立PD控制  作者：平衡小车之家
      入口参数：角度、角速度
      返回  值：直立控制PWM
    **************************************************************************/
    int balance(float Angle, float Gyro)
    {
        float Bias; //偏向
        int balance;
        Bias = Angle - 0;                                //===求出平衡的角度中值 和机械相关//真实角度-期望角度(Angle-Med)
        balance = Balance_Kp * Bias + Gyro * Balance_Kd; //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数
        if (abs(balance) > max)
        {
            balance = balance < 0 ? -max : max;
        }
        else if (abs(Angle) < dead_angle && balance < 250 - push)
        {
            balance += (balance < 0 ? -push : push);
        }
        return balance;
    }
    int velocity(float left, float right, float angle,float acc)
    {
        // static float Velocity, Encoder_Least, Encoder, Movement;
        // static float Encoder_Integral, Target_Velocity;

        //=============速度PI控制器=======================//
        Encoder_Least = (left + right) - 0;             //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零）
        Encoder *= 0.85;                                //===一阶低通滤波器
        Encoder += Encoder_Least * 0.15;                //===一阶低通滤波器
        Encoder_Integral += Encoder;                    //===积分出位移 积分时间：40ms
        Encoder_Integral = Encoder_Integral - Movement; //===接收遥控器数据，控制前进后退
        if (Encoder_Integral > Encoder_Integral_max)
            Encoder_Integral = Encoder_Integral_max; //===积分限幅
        if (Encoder_Integral < -Encoder_Integral_max)
            Encoder_Integral = -Encoder_Integral_max; //===积分限幅
        // if (abs(Encoder_Integral)>15)
        //     Velocity_Ki=Velocity_Ki_2;
        // else
        //     Velocity_Ki=Velocity_Ki;
        Velocity = Encoder * Velocity_Kp + Encoder_Integral * Velocity_Ki,Velocity_Kd*acc; //===速度控制
        Velocity += Velocity < 0 ? -Velocity_push : Velocity_push;
        if (!Accident(angle))
            Encoder_Integral = 0; //小车停止的时候积分清零
        if (abs(Velocity) >= Velocity_max)
            Velocity = Velocity < 0 ? -Velocity_max : Velocity_max;

        return Velocity;
    }

    int turn(float gyro)
    { //转向控制
        static float Turn_Target, Turn, Turn_Convert = 3;
        float Turn_Amplitude = 80, Kp = 2, Kd = 0.001; // PD参数
        if (1 == Flag_Left)
            Turn_Target += Turn_Convert; //根据遥控指令改变转向偏差
        else if (1 == Flag_Right)
            Turn_Target -= Turn_Convert; //根据遥控指令改变转向偏差
        else
            Turn_Target = 0;
        if (Turn_Target > Turn_Amplitude)
            Turn_Target = Turn_Amplitude; //===转向速度限幅
        if (Turn_Target < -Turn_Amplitude)
            Turn_Target = -Turn_Amplitude;
        Turn = -Turn_Target * Kp + gyro * Kd; //===结合Z轴陀螺仪进行PD控制
        return Turn;
    }
};