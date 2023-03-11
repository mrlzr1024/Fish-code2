/**************************************************************************
 **************************************************************************/
#include "main.h"
// #include <WiFi.h>
// #include <HTTPClient.h>

// hw_timer_t *timer = NULL;
//取模方式（阴码+逐行式+顺向）
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Bracelet Loop;
void test();
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
void test()
{
}
