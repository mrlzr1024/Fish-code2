#include "Car_drive.hpp"
int lingdian = 0;
int support = 145;
Drive Car;
void setup()
{
    Car.Car_init();
    Car.Pwm_init();
    Car.Key_init();
    Car.Display_in_begining();
}
float angle;
float tmp;
int tmp2;
float x,v;
void loop()
{
    mpu6050.update();
    tmp = mpu6050.getAccAngleX();
    v+=mpu6050.getAccX()*10;
    x+=v*10;
    Serial.printf("origin:%f,", tmp);
    angle = simpleKalmanFilter.updateEstimate(tmp) + lingdian; // 卡尔曼滤波更新！！！！
    Car.Display_in_running(angle, 12);
    delay(10);
    tmp2 = Car.Pid_angle(angle, mpu6050.getGyroX(), 0);
    tmp2*=0.8;
    tmp2+=Car.Pid_vilocity(x,v,0);
    if (tmp2 < 0)
        Car.Action(1, 0, 0, 1);
    else
        Car.Action(0, 1, 1, 0);

    tmp2 = abs(tmp2);
    tmp2 = tmp2 > 512 ? 512 : tmp2;

    Car.pwm_out(support + tmp2, support + tmp2);
    Car.Adjust();
}
