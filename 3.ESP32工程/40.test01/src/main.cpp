
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
// #include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 mpu;

#define OUTPUT_READABLE_YAWPITCHROLL

#define INTERRUPT_PIN 15 // use pin 2 on Arduino Uno & most boards
#define LED_PIN 2        // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;        // [w, x, y, z]         quaternion container
VectorInt16 aa;      // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity; // [x, y, z]            gravity vector
float euler[3];      // [psi, theta, phi]    Euler angle container
float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = {'$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n'};

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high
void dmpDataReady()
{
  mpuInterrupt = true;
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

const int pin[] = {12, 14, 27, 26

};
void setup()
{
  for (int i = 0; i < 4; i++)
  {
    ledcSetup(i, 5000, 8);    // 通道0， 5KHz，10位解析度
    ledcAttachPin(pin[i], 0); // pin25定义为通道0的输出引脚
  }
// join I2C bus (I2Cdev library doesn't do this automatically)

}

void pwm_out(int channal, int pwm2)
{
  pwm2 = pwm2 > 25 ? 25 : pwm2;
  pwm2 = pwm2 < 0 ? 0 : pwm2;
  // Serial.print(pwm2);
  ledcWrite(channal, pwm2);
}
// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================
int pwm_add[4]={0,0,0,0};
void loop()
{
  // if programming failed, don't try to do anything
  pwm_out(0,25);
  // for (int i = 0; i < 4; i++)
  //     pwm_out(i, 0);
}
