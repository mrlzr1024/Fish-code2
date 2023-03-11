#include "Timer.h"

#include <Arduino.h>
hw_timer_t *timer = NULL;  //定义存放定时器的指针
hw_timer_t *timer2 = NULL; //定义存放定时器的指针
int count = 0;
float getHeartRate = 0;
uint8_t getSpO2 = 0;
//定时器中断函数
void adjest();
void Save_info();
void IRAM_ATTR onTimer()
{
    //   Serial.print("ok");
    //**##不要在中断中执行串行打印!!!!!!!!!!!!!!!!!!!**##//
    // Temp_read();
    count++;
    if (count >= 10)
    {
        Loop.second++;
        count = 0;
    }
    adjest();
}
void adjest()
{
    if (Loop.second >= 60)
    {
        Loop.second = 0;
        Loop.minuse++;
    }
    if (Loop.minuse >= 60)
    {
        Loop.minuse = 0;
        Loop.hour++;
    }
    if (Loop.hour >= 24)
    {
        Loop.hour = 0;
        Loop.day++;
    }
    if (Loop.day >= 365)
    {
        Loop.day = 0;
        Loop.year++;
    }
    if (Loop.mounth >= 12)
    {
        Loop.day = 0;
        Loop.year++;
    }
}
void Save_info()
{
    at24c02_write(Loop.year / 100, 0x03);
    at24c02_write(Loop.year % 100, 0x04);
    at24c02_write(Loop.mounth, 0x05);
    at24c02_write(Loop.day, 0x06);
    at24c02_write(Loop.hour, 0x07);
    at24c02_write(Loop.minuse, 0x08);
}
int step = 0;
int Count_step(int sample)
{
    static int Switch = 0;
    if (sample > 12 && Switch == 0)
    {
        step++;
        Switch = 1;
    }
    else if (sample < 12 && Switch == 1)
    {
        Switch = 0; //复位
    }
    return step;
}

float x, y, z;
void IRAM_ATTR onTimer_2()
{
    // sensors_event_t a, g, temp;
    // mpu.getEvent(&a, &g, &temp);
    // x = a.acceleration.x;
    // y = a.acceleration.y;
    // z = a.acceleration.z;
    // Count_step(sqrt(x * x + y * y + z * z));
}

void Timer0_init()
{
    timer = timerBegin(0, 80, true);            //设置定时器0，80分频，定时器是否上下计数
    timerAttachInterrupt(timer, onTimer, true); //定时器地址指针，中断函数名称，中断边沿触发类型
    timerAlarmWrite(timer, 100000, true);       //操作那个定时器，定时时长单位us，是否自动重装载
    timerAlarmEnable(timer);                    //打开那个定时器
}

void Timer1_init()
{
    timer2 = timerBegin(1, 80, true);              //设置定时器1，80分频，定时器是否上下计数
    timerAttachInterrupt(timer2, onTimer_2, true); //定时器地址指针，中断函数名称，中断边沿触发类型
    timerAlarmWrite(timer2, 500000, true);         //操作那个定时器，定时时长单位us，是否自动重装载
    timerAlarmEnable(timer2);                      //打开那个定时器
}
uint32_t tsLastReport = 0;
void Todo(void *parameter)
{
    while (1)
    {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        x = a.acceleration.x;
        y = a.acceleration.y;
        z = a.acceleration.z;
        x_1 = g.gyro.x;
        y_1 = g.gyro.y;
        z_1 = g.gyro.z;
        temper = temp.temperature;
        Count_step(sqrt(x * x + y * y + z * z));
        // Serial.print(sqrt(x * x + y * y + z * z));
        // Serial.print(",");
        // Serial.println(Count_step(sqrt(x * x + y * y + z * z)));
        delay(250);
    }
}
void Task()
{
    xTaskCreate(Todo, "A_detect", 10000, NULL, 1, NULL);
}

// void onBeatDetected_1()
// {
//     Serial.println("Beat!");
// }

// void Todo_2(void *parameter)
// {
//     PulseOximeter pox_1;
//     uint32_t tsLastReport_1 = 0;
//     if (!pox_1.begin())
//     {
//         Serial.println("FAILED");
//         for (;;)
//             ;
//     }
//     else
//     {
//         Serial.println("SUCCESS");
//     }
//     pox_1.setOnBeatDetectedCallback(onBeatDetected_1);
//     while (digitalRead(0) == HIGH)
//     {
//         pox_1.update();
//         if (millis() - tsLastReport_1 > 1000)
//         {
//             // Serial.print("Heart rate:");
//             HeartRate = pox_1.getHeartRate();
//             // Serial.print(HeartRate);
//             // Serial.print("bpm / SpO2:");
//             SpO2 = pox_1.getSpO2();
//             // Serial.print(SpO2);
//             Serial.println("%");
//             heart_detect(true);
//             tsLastReport_1 = millis();
//         }
//         // delay(250);
//     }
//     Serial.println("Ending task 2");
//     pox_1.shutdown();
//   vTaskDelete(NULL);
// }

// void Task_2()
// {
//     xTaskCreate(Todo_2, "B_detect", 10000, NULL, 2, NULL);
// }