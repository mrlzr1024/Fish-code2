

#include "main.h"
// #include <BluetoothSerial.h>

MPU6050 mpu6050(Wire);
Display OLED;
PID_Contral pid;
Kalman_filtering fl;
hw_timer_t *tim1 = NULL;
// BluetoothSerial SerialBT;
int cont = 0;
// bool Accident(float angle);
// void output(float pidd);
void time_init();

float angle = 0, gyro = 0, l_sp = 0, r_sp = 0;
int pidd = 0;
unsigned int count = 0;
long d_time = 0, im = 0;
int sup = 0; //刷新时间 /ms
float mpu_init_angle;
int velocity_pwm = 0, balance_pwm = 0;
int CMD, MOVE;
int direction_support = 0;
void setup()
{
    pinMode(14, INPUT_PULLUP);

    // 初始化日志打印串口
    Serial.begin(115200);
    // SerialBT.begin("ESP-Car"); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    OLED.display_init();

    OLED.Car_init("电机", "正在配置");
    Car_init();
    Action(1, 0, 1, 0);
    encode_init(); // 100===3.5  50===0.98  200===5.50(max)
    Wire.begin(23, 22);
    // OLED.Car_init("电机", "完成");
    delay(500);
    if (digitalRead(14) == LOW)
    {
        // pid.Encoder_Integral = 0;
        Action(0, 0, 0, 0);
        OLED.Center("Oh on ! =(");
        while (1)
            ;
    }
    OLED.Car_init("加速度计", "8动");
    mpu6050.begin();
    mpu6050.calcGyroOffsets(true);
    OLED.Car_init("加速度计", "完成");
    // delay(500);

    OLED.Car_init("Filter", "正在校准");
    fl.Filter_init(&mpu6050);
    OLED.Car_init("Filter", "已完成");
    // delay(500);

    // OLED.Car_init("定时器", "正在配置");
    // time_init(); // 配置定时器 这里使用的是定时器0(一共四个0123)
    // OLED.Car_init("定时器", "完成");

    // OLED.Center("=) ? =(");
    // // delay(300);
    // OLED.Center("Let's dance ?");

    digitalWrite(2, HIGH);

    mpu6050.update();
    mpu_init_angle = mpu6050.getAngleX();

    // pwm_write(250, 250);
}
/*
 * 原始数据:90~180 -180~-90
 * (直立)=-176 (前90°)=90 (后90°)=-90
 * 角速度：
 *
 *
 */
int step=20;
void loop()
{
    
back:
    im = millis();
    // angle = fl.Filtering(&mpu6050)[0];
    mpu6050.update();
    angle = mpu6050.getAngleX() - mpu_init_angle;
    gyro = mpu6050.getGyroX();

    l_sp = left_speed();
    r_sp = right_speed();
    // // Serial.print(angle);

    // if (SerialBT.available())
    // {
    //     CMD = SerialBT.read();
    //     Serial.println(CMD);
    // }

    if (millis() - d_time >= 10)
    {
        OLED.show_info(angle, pid.Encoder_Integral, velocity_pwm, mpu6050.getAccX());
        //SerialBT.println(pid.Encoder_Integral);
        d_time = millis();
    }
    if (!Accident(angle))
    {
        pid.Encoder_Integral = 0;
        velocity_pwm = 0;
        goto back;
    }
    if (cont >= 2)
    {
        // velocity_pwm = pid.velocity(l_sp, r_sp);
        cont = 0;
    }
    if (CMD == 0x01) //后退
    {
        Serial.println(":OK");
        pid.Encoder_Integral += step;
        CMD = 0X00;
    }
    else if (CMD == 0x02) //前进
    {
        Serial.println(":OK");
        pid.Encoder_Integral += -step;
        CMD = 0X00;
    }
    else if (CMD == 0x03) //停止
    {
        Serial.println(":OK");
        pid.Movement = -0;
        pid.Encoder_Integral = 0;
        CMD = 0X00;
    }
    else if (CMD == 0x04) //向左
    {
        Serial.println(":OK");
        // pid.Flag_Right = 0;
        // pid.Flag_Left = 1;
        CMD = 0X00;
        output(pidd, -1);
        delay(10);
        // output(pidd, 0);
        goto back;
    }
    else if (CMD == 0x05) //向右
    {
        Serial.println(":OK");
        // pid.Flag_Right = 1;
        // pid.Flag_Left = 0;
        CMD = 0X00;
        output(pidd, 1);
        delay(10);
        // output(pidd, 0);
        goto back;
    }
    else if (CMD == 0x06) //向右
    {
        Serial.println(":OK");
        step+=20;
        CMD = 0X00;
    }
     else if (CMD == 0x07) //向右
    {
        Serial.println(":OK");
        step-=20;
        CMD = 0X00;
    }
    // else
    velocity_pwm = pid.velocity(l_sp, r_sp, angle,mpu6050.getAccX());
    balance_pwm = pid.balance(angle, gyro);
    // pidd = pid.velocity(l_sp, r_sp, angle); //+ pid.velocity(l_sp, r_sp);
    pidd = balance_pwm + velocity_pwm; //+ pid.velocity(l_sp, r_sp);
    // Serial.println(angle);

    // direction_support = pid.turn(mpu6050.getGyroZ());
    delay(2);
    count++;
    output(pidd, direction_support);

    sup = millis() - im; //统计反应时间
    if (digitalRead(14) == LOW)
    {
        // pid.Encoder_Integral = 0;
        Action(0, 0, 0, 0);
        while (digitalRead(14) == HIGH)
            ;
    }
}

// 定时器中断回调函数=====执行=====
// void IRAM_ATTR wc()
// {
//     //  mpu6050.update();
// }

// void time_init()
// {
//     tim1 = timerBegin(2, 80, true);
//     timerAttachInterrupt(tim1, wc, true);
//     timerAlarmWrite(tim1, 10000, true); // 1000us一次
//     timerAlarmEnable(tim1);
// }
