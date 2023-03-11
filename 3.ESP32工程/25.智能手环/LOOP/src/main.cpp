/**************************************************************************
 **************************************************************************/
#include "main.h"
#include <Arduino.h>
// #include <WiFi.h>
// #include <HTTPClient.h>

// hw_timer_t *timer = NULL;
//取模方式（阴码+逐行式+顺向）
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Bracelet Loop;
void update();
void fill();

void setup()
{
    ADXL346_init();
    // test();
    // Serial.begin(115200);
    // Hear_Detect_init();
    Display_init(); // oled初始化
    Encode_init();  //编码器初始化
    Temp_init();    //温度模块初始化
    Timer0_init();  //定时器0初始化(1s)
    // Timer1_init();  //定时器1初始化(0.5s)
    RTC_Init();
    Task();
}

void loop()
{
    versatile_encoder->ReadEncoder(); //检测输入
    Save_info();
    
}

String data_send;

void update()
{
    fill();
    Serial.println("U" + data_send);
    data_send = "";
}

void fill()
{
    // U 2022 12 11 22 10 00003 100
    // U 2255 06 11 22 43 00006 0.0000
    data_send += String(Loop.year);
    if (Loop.mounth / 10 == 0)
    {
        data_send += ("0" + String(Loop.mounth));
    }
    else
    {
        data_send += String(Loop.mounth);
    }
    if (Loop.day / 10 == 0)
    {
        data_send += "0" + String(Loop.day);
    }
    else
    {
        data_send += String(Loop.day);
    }
    if (Loop.hour / 10 == 0)
    {
        data_send += "0" + String(Loop.hour);
    }
    else
    {
        data_send += String(Loop.hour);
    }
    if (Loop.minuse / 10 == 0)
    {
        data_send += "0" + String(Loop.minuse);
    }
    else
    {
        data_send += String(Loop.minuse);
    }
    data_send += String(step / 10000);
    data_send += String(step % 10000 / 1000);
    data_send += String(step % 1000 / 100);
    data_send += String(step % 100 / 10);
    data_send += String(step % 10 / 1);
    // HeartRate
    data_send += String(int(HeartRate) / 100);
    data_send += String(int(HeartRate) % 100 / 10);
    data_send += String(int(HeartRate) % 10);
}