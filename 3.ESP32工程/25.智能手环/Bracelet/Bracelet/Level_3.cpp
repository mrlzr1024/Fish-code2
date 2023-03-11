#include "Level_3.h"
void Clock_1(String data, int x, int y, int size);
void heart_detect();
void Temperature_detect();
void Gradienter_detect();
void Date_detect();
void Step_detect();
void Heart_detect(void);
void WLAN_detect();

bool Clock_switch;
bool Hear_Detect_switch;
int i = 0;

void handlePress() //按下去
{
    Clock_switch = false;
    if (level_1_Control == Standard)
    {
        switch (Mode_1)
        {
        case Clock:
            // Clock_total();
            delay(500);
            while (digitalRead(0) == HIGH)
            {
                Clock_total();
                // delay(50);
            }
            break;
        case Step:
            delay(500);
            while (digitalRead(0) == HIGH)
            {
                Step_detect();
            }
            break;
        case Heart_Rate:
            delay(500);
            Heart_detect();
            // Task_2();
            // pox.shutdown();
            break;
        case TEmperature:
            Temp_init();
            delay(750);
            while (digitalRead(0) == HIGH)
            {
                Temperature_detect();
                delay(500);
            }
            break;
        case Gradienter:
            // ADXL346_init();
            delay(500);
            while (digitalRead(0) == HIGH)
            {
                Gradienter_detect();
            }
            break;
        case DATE:
            delay(500);
            while (digitalRead(0) == HIGH)
            {
                Date_detect();
            }
        case WLAN:
            delay(500);
            while (digitalRead(0) == HIGH)
            {
                WLAN_detect();
            }
            break;
        default:
            break;
        }
    }
    // Display("+");
}
void Clock_total()
{
    display.clearDisplay();
    if (Loop.hour < 10)
    {
        Clock_1("0" + String(Loop.hour), 32, 0, 3);
    }
    else
    {
        Clock_1(String(Loop.hour), 32, 0, 3);
    }

    if (Loop.minuse < 10)
    {
        Clock_1("0" + String(Loop.minuse), 32, 32, 3);
    }
    else
    {
        Clock_1(String(Loop.minuse), 32, 32, 3);
    }
    Clock_1(String(Loop.second), 70, 56, 1);
    display.display(); // Show initial text
}
void Clock_1(String data, int x, int y, int size)
{
    // display.clearDisplay();
    display.setTextSize(size); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(data);
}

float HeartRate = 0;
uint8_t SpO2 = 0;
void heart_detect(bool Switch)
{
    if (Switch)
    {
        // Serial.print("Heart rate:");
        // Serial.print(HeartRate);
        // Serial.print("bpm / SpO2:");
        // Serial.print(SpO2);
        // Serial.println("%");

        display.clearDisplay();
        display.setTextSize(1); // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Heart rate:");
        display.println(HeartRate);
        display.println("bpm / SpO2:");
        display.print(SpO2);
        display.println("%");
        display.display(); // Show initial text
    }
}

void onBeatDetected_1()
{
    Serial.println("Beat!");
}
/*
函数名：Heart_detect
简述 ：开启心率探测器，探测心率，关闭探测器
备注：用一次开一次，用完就关(GPIO0=0时关闭)
*/
void Heart_detect(void)
{
    PulseOximeter pox_1;
    uint32_t tsLastReport_1 = 0;
    if (!pox_1.begin())
    {
        Serial.println("FAILED");
        for (;;)
            ;
    }
    else
    {
        Serial.println("SUCCESS");
    }
    pox_1.setOnBeatDetectedCallback(onBeatDetected_1);
    while (digitalRead(0) == HIGH)
    {
        pox_1.update();
        if (millis() - tsLastReport_1 > 1000)
        {
            // Serial.print("Heart rate:");
            HeartRate = pox_1.getHeartRate();
            // Serial.print(HeartRate);
            // Serial.print("bpm / SpO2:");
            SpO2 = pox_1.getSpO2();
            // Serial.print(SpO2);
            Serial.println("%");
            heart_detect(true);
            tsLastReport_1 = millis();
        }
        // delay(250);
    }
    Serial.println("Ending task 2");
    pox_1.shutdown();
    // vTaskDelete(NULL);
}

void Temperature_detect()
{
    display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Temperature:");
    display.setTextSize(3);
    display.println(Temp_read());
    display.display(); // Show initial text
}
float x_1, y_1, z_1, temper;
void Gradienter_detect()
{
    /* Get new sensor events with the readings */
    display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("X:");
    display.println(x_1);
    display.println("Y:");
    display.println(y_1);
    display.println("Z:");
    display.println(z_1);
    display.println("Temperature:");
    display.println(String(temper) + "  degC");
    display.display(); // Show initial text
    delay(500);
}

void Date_detect()
{
    display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setCursor(0, 0);
    display.println(Loop.year);
    display.setCursor(32, 8);
    display.setTextSize(2);
    display.println(Loop.mounth);
    display.setCursor(48, 24);
    display.setTextSize(5);
    display.println(Loop.day);
    display.display();
}

void Step_detect()
{
    display.clearDisplay();
    display.setTextSize(6); // Draw 2X-scale text
    display.setCursor(48, 0);
    display.println(step);
    display.display();
}

void WLAN_detect()
{
    // display.clearDisplay();
    // display.setTextSize(3); // Draw 2X-scale text
    // display.setCursor(48, 0);
    // if (Wlan_init())
    // {
    //     display.println("OK");
    // }
    // else
    // {
    //     display.println("Wc Tnnd");
    // }
    // display.display();
}