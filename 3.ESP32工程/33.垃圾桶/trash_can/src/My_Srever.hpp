#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
void Server_init(int Server_freq = 50)
{
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(Server_freq); // Analog servos run at ~50 Hz updates
}
class Servo
{
    /**
     * PWM范围：0~4096
     * 最小PWM：150(0°) 2.5%
     * 最大pwm: 600(180°)   12.5%
     */
private:
    int Bias = 0; //电机偏置
    float k = 1;  //角度映射参数
    int Servo_num = 0;

public:
    Servo(int Servo_num, int Bias = 0, int Range = 180)
    { /**
       * @brief 声明舵机对象
       * int Servo_num:第几个舵机
       * int Bias：初始角度偏差
       * int Range：舵机转动范围
       */
        this->Servo_num = Servo_num;
        this->Bias = Bias;
        if (Range == 180)
            k = 1;
        else if (Range == 360)
            k = 2;
    }

    void Move(int angle)
    {
        int microsec;
        //加入偏置
        angle /= k;
        if ((angle > 180 || angle < 0))
        {
            angle=angle==180?180:0;
        }
        // if(Servo_num==0){
        //     Bias+=(angle>=90)?5:-5;
        // }
        angle += Bias;
        microsec = int(angle / 180.0 * 2000) + 500;
        // Serial.println(angle);
        pwm.writeMicroseconds(Servo_num, microsec);
    }
};