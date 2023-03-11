#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class My_Server
{
    /*
     * PWM范围：0~4096
     * 最小PWM：150(0°) 2.5%
     * 最大pwm: 600(180°)   12.5%
     */
private:
public:
    Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
    void Server_init(int Server_freq = 50)
    {
        pwm.begin();
        pwm.setOscillatorFrequency(27000000);
        pwm.setPWMFreq(Server_freq); // Analog servos run at ~50 Hz updates
    }
    void Move(int servonum, int angle)
    {
        int microsec;
        if (angle > 180 || angle < 0)
            return;
        microsec = int(angle / 180.0* 2000) + 500;
        Serial.println(microsec);
        pwm.writeMicroseconds(servonum, microsec);
    }
   
};