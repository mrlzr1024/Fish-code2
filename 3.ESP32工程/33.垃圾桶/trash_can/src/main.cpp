#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "My_Srever.hpp"
#include "Arm.hpp"
#include <MPU6050_tockn.h>

void Timer_init();
MPU6050 mpu6050(Wire);

uint8_t servonum = 1;
Servo servo_0(0, 15, 360);
Servo servo_1(1, -5, 180);
Servo servo_2(2, 5, 180);
Servo servo_3(3, 0, 180);
Servo servo_4(4, 0, 180);
Arm arm;
hw_timer_t *timer = NULL; //声明一个定时器
unsigned int count = 0;
int Step_motor = 0;
int Step_dir = 1;
int move_flag = 0;
int c_flag = 0,angle=0;
void setup()
{
    Serial.begin(115200);
    Server_init();
    Timer_init();
    arm.Set_Param(19, 28);
    servo_1.Move(180);
    servo_0.Move(0);
    servo_2.Move(0);
    // mpu6050.begin();
    // mpu6050.calcGyroOffsets(true);
    delay(10);
}
String cmd;
char x[3], d[3], z[3] = {0, 0, 0};
int x1 = 0, d1 = 10;
void loop()
{
    // servo_4.Move(0);
    // delay(1000);
    // servo_4.Move(45);
    // delay(1000);
    // mpu6050.update();
    while (Serial.available())
        cmd = Serial.readString();
    if (cmd == "z")
    {
        servo_1.Move(180);
        servo_0.Move(0);
        servo_2.Move(0);
        Serial.println("OK");
        goto bad;
    }
    else if (cmd[0] == 'l')
    {
        digitalWrite(Step_dir, LOW);
        z[0] = cmd[1];
        z[1] = cmd[2];
        z[2] = cmd[3];
        move_flag = 1;
        cmd = "";
        goto bad;
    }
    else if (cmd[0] == 'r')
    {
        digitalWrite(Step_dir, HIGH);
        z[0] = cmd[1];
        z[1] = cmd[2];
        z[2] = cmd[3];
        move_flag = 1;
        cmd = "";
        goto bad;
    }
    else if (cmd[0] == 'O')
    {
        servo_3.Move(15);
        cmd = "";
        goto bad;
    }
    else if (cmd[0] == 'C')
    {
        servo_3.Move(140);
        cmd = "";
        goto bad;
    }
    // else if (cmd[0] == 'p')
    // {
    //     c_flag = 1;
    //     angle = mpu6050.getAngleX();
    //     servo_2.Move(90 - int(angle));
    //     cmd = "";
    // }
    else if(cmd!="")
    {
        x[0] = cmd[0];
        x[1] = cmd[1];
        x[2] = cmd[2];
        d[0] = cmd[4];
        d[1] = cmd[5];
        Serial.printf("x=%d,d=%d z=%d count= %d \n", atoi(x), atoi(d), atoi(z), count);
        Serial.println("");
        cmd="";
    }

    // servo_2.Move(0);
    arm.Set_Param(19, 28);
    // // for (int i = -25; i <= 25; i++)
    // // {
    // //     j+=0.5;
    d1 = atoi(d);
    x1 = atoi(x);
    // angle=mpu6050.getAngleX();
    // Serial.print("angleX : ");
    // Serial.println(90+(int(angle)));
    if (!arm.Set_target(d1, x1))
    {
        goto bad;
    }
    arm.Calculation();
    servo_1.Move(arm.To_Angle(arm.Get_Rad_2()));

    servo_0.Move(arm.To_Angle(arm.Get_Rad_1()) + 90);
    servo_2.Move(arm.To_Angle(arm.Get_Rad_3()) );
    
bad:;
}

void IRAM_ATTR onTimer()
{ //中断函数

    if (count > 65535 || count / 50 >= atoi(z))
    {
        count = 0;
        move_flag = 0;
    }
    if (move_flag && count / 50 < atoi(z))
    {
        count++;
        digitalWrite(Step_motor, !digitalRead(Step_motor));
    }
    // digitalWrite(Step_motor, !digitalRead(Step_motor));
}
void Timer_init()
{
    timer = timerBegin(0, 80, true);             //定时器0，80分频
    timerAttachInterrupt(timer, &onTimer, true); //调用中断函数
    timerAlarmWrite(timer, 100, true);          // 计数10000次
    timerAlarmEnable(timer);                     //定时器使能
    pinMode(Step_motor, OUTPUT);
    pinMode(Step_dir, OUTPUT);
    // timerDetachInterrupt(timer); //关闭定时器
}