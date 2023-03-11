
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "SSD1306.h" // legacy include: `#include "SSD1306.h"`
#include "car.hpp"
#include <BluetoothSerial.h>

#define balence_kp 0 // 8  //   <=25
#define balence_kd 8
#define Dead_zone_l 5
#define Dead_zone_r 10
MPU6050 mpu6050(Wire);
// BluetoothSerial SerialBT;
int pwm_pin[] = {pwm_pin_A, pwm_pin_B};
int channal[] = {channal_A, channal_B};
int pin[] = {logic_pin_A, logic_pin_B, logic_pin_C, logic_pin_D};
bool statue[] = {
    1, 0, 0, 1};

long timer = 0;

SSD1306 display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h
bool staut = LOW;

void Action(int a, int b, int c, int d); //更改电机状态
void pwm_out(int duty_a, int duty_b);    // pwm输出
void time_init();
int CMD, MOVE;
void setup()
{
    Serial.begin(115200); // 如果没有参数传入则默认是蓝牙名称是: "ESP32"
    for (int i = 0; i < 4; i++)
    {
        pinMode(pin[i], OUTPUT);
        digitalWrite(pin[i], statue[i]);
        // staut =! staut;
    }
   
    for (int i = 0; i < 2; i++)
    {
        ledcSetup(channal[i], 1000, 8);

        // attach the channel to the GPIO to be controlled
        ledcAttachPin(pwm_pin[i], channal[i]);
    }
    ledcWrite(channal[0], 0);
    ledcWrite(channal[1], 0);
    Serial.begin(115200);
    Wire.begin();

    display.init();
    display.flipScreenVertically(); //反转屏幕

    display.setContrast(255);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);

    display.clear();
    display.drawString(display.getWidth() / 8, 15, "Servo init...");
    display.display();

    delay(500);
    display.clear();
    display.drawString(display.getWidth() / 8, 15, "mpu6050 init in 3s...");
    display.display();
     Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
    // Action(1, 0, 1, 0);
    // pwm_out(35, 25);
}
float x = 0, g_x;
int pwm;
void loop()
{
    mpu6050.update();
    display.clear();
    display.drawString(display.getWidth() / 8, 15, String(mpu6050.getAccAngleX()));
    display.display();
    delay(500);
}

void Action(int a, int b, int c, int d)
{
    int st[] = {a, b, c, d};
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(pin[i], st[i]);
    }
}
void pwm_out(int duty_a, int duty_b)
{
    duty_a += Dead_zone_l + duty_a * 1.17;
    duty_b += Dead_zone_r + duty_b * 1.17;
    if (duty_a > 250 || duty_b > 250)
    {
        duty_a = 250;
        duty_b = 250;
    }
    ledcWrite(channal[0], duty_a);
    ledcWrite(channal[1], duty_b);
}
