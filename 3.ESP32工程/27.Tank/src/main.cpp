#include "main.h"
#include "BluetoothSerial.h"
void Action(bool a, bool b, bool c, bool d);
int pin[] = {
    27, 26, 25, 33};
BluetoothSerial SerialBT;
void Action(bool a, bool b, bool c, bool d);
int calculatePWM(int degree);

void setup()
{
    Serial.begin(115200); // 串口初始化
    Serial.println();
    // Task_init();
    for (int i = 0; i < 4; i++)
    {
        pinMode(pin[i], OUTPUT);
    }
    // ledcSetup(8, 50, 8);  // 设置通道
    // ledcSetup(9, 50, 8);  // 设置通道
    // ledcAttachPin(12, 8); // 将通道与对应的引脚连接
    // ledcAttachPin(14, 9); // 将通道与对应的引脚连接
    SerialBT.begin("ESP32test");
    ledcSetup(10, 1000, 8); // 设置通道
    ledcSetup(11, 1000, 8); // 设置通道
    ledcAttachPin(2, 10);   // 将通道与对应的引脚连接
    ledcAttachPin(14, 11);   // 将通道与对应的引脚连接
}
int Delay = 100;
bool mode_auto = 1;
int Adjust = 0;
char cmmd=' ';
void loop()
{
    while(SerialBT.available())
    {
        cmmd=SerialBT.read();
        Serial.println(cmmd);
    }
    if (cmmd == 0X03) // 前进
    {
        Serial.println(cmd);
        Action(0, 1, 1, 0);
        cmmd=' ';
        // int 180 = cmd.toInt() * 256 / 100;
        ledcWrite(10, 180 );
        ledcWrite(11, 180);
        if (mode_auto)
        {
            delay(Delay);
            Action(0, 0, 0, 0);
        }
        // delay(100);
        // Action(0, 0, 0, 0);
    }
    else if (cmmd == 0X02) // 左转
    {
        Action(1, 0, 1, 0);
        cmmd=' ';
        ledcWrite(10, 150);
        ledcWrite(11, 150);
        if (mode_auto)
        {
            delay(Delay);
            Action(0, 0, 0, 0);
        }
    }
    else if (cmmd == 0X01) // 右转
    {
        Action(0, 1, 0, 1);
        cmmd=' ';
        ledcWrite(10, 150);
        ledcWrite(11, 150);
        if (mode_auto)
        {
            delay(Delay);
            Action(0, 0, 0, 0);
        }
    }
    else if (cmmd == 0X04) // 后退
    {
        Action(1, 0, 0, 1);

        cmmd=' ';
        ledcWrite(10, 180 );
        ledcWrite(11, 180);
        if (mode_auto)
        {
            delay(Delay);
            Action(0, 0, 0, 0);
        }
        // delay(100);
        // Action(0, 0, 0, 0);
    }
    else if (cmmd == 'S') // 停止
    {
        // stop
        Action(0, 0, 0, 0);
        cmmd=' ';
    }
    // else if (cmd[0] == 'D') // 行动时间
    // {
    //     // delay
    //     cmd[0] = ' ';
    //     Delay = cmd.toInt();
    // }
    // else if (cmd[0] == 'J') // 校准
    // {
    //     // delay
    //     cmd[0] = ' ';
    //     Adjust = cmd.toInt();
    // }
    // else if (cmd == "Auto")
    // { // 自动模式
    //     mode_auto = 1;
    // }
    // else if (cmd == "Manual")
    // { // 手动模式
    //     mode_auto = 0;
    // }
    // else if (cmd[0] == 'X') // 舵机X轴
    // {
    //     // 舵机X轴
    //     cmd[0] = ' ';
    //     int angle = cmd.toInt();
    //     Serial.printf("X轴舵机转:%d", angle); // 从串口打印
    //     ledcWrite(8, calculatePWM(angle));    // 输出PWM
    //     Serial.printf("value=%d,calcu=%d\n", angle, calculatePWM(angle));
    // }
    // else if (cmd[0] == 'Y') // 舵机Y轴
    // {
    //     // 舵机Y轴
    //     cmd[0] = ' ';
    //     int angle = cmd.toInt();
    //     Serial.printf("Y轴舵机转:%d", angle); // 从串口打印
    //     ledcWrite(9, calculatePWM(angle));    // 输出PWM
    //     Serial.printf("value=%d,calcu=%d\n", angle, calculatePWM(angle));
    // }
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
// #include <Arduino.h>

// int freq = 50;      // 频率(20ms周期)
// int channel = 8;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
// int resolution = 8; // 分辨率
// const int led = 12;

int calculatePWM(int degree)
{                               // 0-180度
                                // 20ms周期，高电平0.5-2.5ms，对应0-180度角度
    const float deadZone = 6.4; // 对应0.5ms（0.5ms/(20ms/256）)
    const float max = 32;       // 对应2.5ms
    if (degree < 0)
        degree = 0;
    if (degree > 180)
        degree = 180;
    return (int)(((max - deadZone) / 180) * degree + deadZone);
}

// void setup()
// {
//   Serial.begin(115200);
//   ledcSetup(channel, freq, resolution); // 设置通道
//   ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
//   ledcAttachPin(14, 9);          // 将通道与对应的引脚连接
// }

// void loop()
// {
// //   for (int d = 0; d <= 180; d += 10)
// //   {
// //     ledcWrite(channel, calculatePWM(d)); // 输出PWM
// //     Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
// //     delay(1000);
// //   }
//    for (int d = 0; d <= 90; d += 10)
//   {
//     ledcWrite(9, calculatePWM(d)); // 输出PWM
//     Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
//     delay(1000);
//   }
// }
