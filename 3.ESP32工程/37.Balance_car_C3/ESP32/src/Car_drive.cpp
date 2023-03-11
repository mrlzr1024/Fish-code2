#include "Car_drive.hpp"

MPU6050 mpu6050(Wire);
SSD1306 display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h
SimpleKalmanFilter simpleKalmanFilter(5, 5, 0.8);

void Drive::Action(int a, int b, int c, int d)
{
    statue[0] = a;
    statue[1] = b;
    statue[2] = c;
    statue[3] = d;
    for (int i = 0; i < 4; i++)
    {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], statue[i]);
    }
}

void Drive::pwm_out(int duty_a, int duty_b) // pwm输出
{
    duty_a=duty_a>max_pwm?max_pwm:duty_a;
    duty_b=duty_b>max_pwm?max_pwm:duty_b;
    duty_a=duty_a<0?0:duty_a;
    duty_b=duty_b<0?0:duty_b;
    ledcWrite(channal[0], duty_a);
    ledcWrite(channal[1], duty_b);
}

//  void Drive::time_init();

void Drive::Pwm_init()
{
    for (int i = 0; i < 2; i++)
    {
        ledcSetup(channal[i], 1000, resolution);
        ledcAttachPin(pwm_pin[i], channal[i]);
    }
    ledcWrite(channal[0], 0);
    ledcWrite(channal[1], 0);
}

void Drive::Car_init()
{
    Serial.begin(115200);
    for (int i = 0; i < 4; i++)
    {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], statue[i]);
    }
}

void Drive::Key_init()
{
    for (int i = 0; i < 4; i++)
    {
        pinMode(key[i], INPUT_PULLUP);
    }
}

void Drive::Display_in_begining()
{
    Wire.begin();
    display.init();
    display.flipScreenVertically(); // 反转屏幕
    display.setContrast(255);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    int a = 10;
    display.drawProgressBar(0, 10, 128, 8, a);
    display.drawString(display.getWidth() / 8, 30, "MPU init...");
    display.drawString(display.getWidth() / 2, 40, "IX");
    display.display();
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    display.clear();
    while (a <= 100)
    {
        a += 1;
        display.drawProgressBar(0, 10, 128, 8, a);
        display.drawString(display.getWidth() / 8, 30, "Complete...");
        display.drawString(display.getWidth() / 2, 40, "IX");
        display.display();
        delay(10);
    }
}

void Drive::Display_in_running(float angle, int size)
{
    display.clear();
    display.drawString(0, size, String(angle));
    display.drawString(50, size, set[mindex]);
    display.drawString(0, size * 2, "Bp=" + String(parameter[0]) + "    Vp=" + String(parameter[3]));
    display.drawString(0, size * 3, "Bi=" + String(parameter[1]) + "    Vi=" + String(parameter[4]));
    display.drawString(0, size * 4, "Bd=" + String(parameter[2]) + "    Vd=" + String(parameter[5]));
    display.display();
    Serial.printf("kalman:%f \r\n", angle);
}

void Drive::Adjust()
{
    if (digitalRead(12) == LOW)
    {
        parameter[mindex]+=0.1;
        while (digitalRead(12) == LOW)
            ;
    }
    else if (digitalRead(13) == LOW)
    {
        parameter[mindex]-=0.1;
        while (digitalRead(13) == LOW)
            ;
    }
    if (digitalRead(1) == LOW)
    {
        mindex++;
        while (digitalRead(1) == LOW)
            ;
    }
    else if (digitalRead(0) == LOW)
    {
        mindex--;
        while (digitalRead(0) == LOW)
            ;
    }
    mindex = mindex < 0 ? 5 : mindex;
    mindex = mindex > 5 ? 0 : mindex;
}

float Drive::Pid_angle(float angle, float rad, float acc)
{

    // float parameter[6] = {
    //     0, // B_KP ,//比例项
    //     0, // B_KI ,//积分项
    //     0, // B_KD ,//微分项
    //     0, // V_KP ,
    //     0, // V_KI ,
    //     0, // V_KD
    // };
    float Mechanical_balance=0;
    float pwm_out = parameter[0] * (angle - Mechanical_balance) +//p
                    parameter[2] * rad +//d
                    parameter[1] * acc;//i
    return pwm_out;
}
float Drive::Pid_vilocity(float p, float i, float d)
{

    // float parameter[6] = {
    //     0, // B_KP ,//比例项
    //     0, // B_KI ,//积分项
    //     0, // B_KD ,//微分项
    //     0, // V_KP ,
    //     0, // V_KI ,
    //     0, // V_KD
    // };
    float Mechanical_balance=0;
    float pwm_out = parameter[3] * p +//p
                    parameter[4] * i +//i
                    parameter[5] * d;//d
    return pwm_out;
}
