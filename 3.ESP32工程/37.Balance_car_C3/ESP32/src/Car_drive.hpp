#include <MPU6050_tockn.h>
#include <Wire.h>
#include "SSD1306.h" // legacy include: `#include "SSD1306.h"`
#include "Car_pin.hpp"
#include <BluetoothSerial.h>
#include <SimpleKalmanFilter.h>

#define pwm_pin_A 10
#define pwm_pin_B 6

#define channal_A 3
#define channal_B 1

#define logic_pin_A 2
#define logic_pin_B 3
#define logic_pin_C 8
#define logic_pin_D 9

#define key_pin_A 12
#define key_pin_B 13
#define key_pin_C 1
#define key_pin_D 0

extern MPU6050 mpu6050;
extern SSD1306 display;
extern SimpleKalmanFilter simpleKalmanFilter;
// MPU6050 mpu6050(Wire);
// SSD1306 display(0x3c, SDA, SCL); // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h
// SimpleKalmanFilter simpleKalmanFilter(5, 5, 1);

class Drive
{
private:
    int pwm_pin[2] = {pwm_pin_A, pwm_pin_B};
    int channal[2] = {channal_A, channal_B};
    int pin[4] = {logic_pin_A, logic_pin_B, logic_pin_C, logic_pin_D};
    int key[4] = {key_pin_A, key_pin_B, key_pin_C, key_pin_D};
    bool statue[4] = {1, 0, 0, 1};
    float parameter[6] = {
        5.56, // B_KP ,
        28, // B_KI ,
        0.13, // B_KD ,
        0, // V_KP ,
        0, // V_KI ,
        0, // V_KD
    };
    String set[6] = {
        "B_KP",//比例（P）
        "B_KI",//积分（I）
        "B_KD",//微分（D）
        "V_KP",
        "V_KI",
        "V_KD",
    };
    int mindex = 0;
    int resolution=10;
    int max_pwm=512;


public:
    void Action(int a, int b, int c, int d); // 更改电机状态
    void pwm_out(int duty_a, int duty_b);    // pwm输出
    void time_init();
    void Car_init();
    void Pwm_init();
    void Key_init();
    void Adjust();
    void Display_in_begining();                       // 开机动画
    void Display_in_running(float angle_x, int size); // 运行动画
    float Pid_angle(float angle, float rad, float acc);
    float Pid_vilocity(float p, float i, float d);
};
