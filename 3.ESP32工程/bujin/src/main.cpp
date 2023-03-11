/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "My_Srever.hpp"
// called this way, it uses the default address 0x40
// Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 1;
My_Server ser;
void setup() {
  Serial.begin(115200);
//   pwm.begin();
  ser.Server_init();
//  pwm.setOscillatorFrequency(27000000);
//   pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}


void loop() {
//     for (uint16_t microsec = USMIN; microsec < USMAX; microsec++) {
//     pwm.writeMicroseconds(servonum, microsec);
//   }

//   delay(500);
//   for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
//     pwm.writeMicroseconds(servonum, microsec);
//   }

//   delay(500);
ser.Move(1,150);
delay(3000);
ser.Move(1,0);
delay(3000);
}


 
// hw_timer_t * timer = NULL;            //声明一个定时器
//  int count=0;
 
// void IRAM_ATTR onTimer() {            //中断函数
//  count++;
//  digitalWrite(0,!digitalRead(0));
  
// }
 
 
// void setup() {
//   Serial.begin(115200);                        
//   timer = timerBegin(0, 80, true);                //初始化
//   timerAttachInterrupt(timer, &onTimer, true);    //调用中断函数
//   timerAlarmWrite(timer, 1000, true);        //timerBegin的参数二 80位80MHZ，这里为1000000  意思为1秒
//   timerAlarmEnable(timer);                //定时器使能
//  pinMode(0,OUTPUT);
// //timerDetachInterrupt(timer);            //关闭定时器
// }
 
 
// void loop() {
//  Serial.println(count);
//  delay(500);
//  if(count>65535){
//     count=0;
//  }
// }