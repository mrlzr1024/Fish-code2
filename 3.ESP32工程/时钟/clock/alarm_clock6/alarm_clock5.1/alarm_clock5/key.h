/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-06-11 15:42:23
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-06-11 17:13:33
 * @FilePath: \alarm_clock6\key.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _KEY_H
#define _KEY_H

#include "key.h"
/// bug:休眠键

// WiFi库
#include <WiFi.h>
#include "hz.h"

// DS1307库
#include <Wire.h>
#include "RTClib.h"

// 串口重映射相关
#include <HardwareSerial.h> //导入ESP32串口操作库,使用这个库我们可以把串口映射到其他的引脚上使用
//我们测试需要用到的串口，ESP32一共有3个串口，串口0应该是用于程序烧写和打印输出调试用的，所以我们只用1和2
extern HardwareSerial MySerial_stm32;

#include <Preferences.h>

#include "JQ8900.h"

#include <Ticker.h> //调用Ticker.h库

#include "BluetoothSerial.h" //调用串口蓝牙函数库

#include <esp_sleep.h>

/*
   硬件模块
   主控：esp-32
   时钟源模块：DS307
   温度传感器：LM35D电子模拟温度传感器
   显示模块：1.8寸串口屏
   语音播报模块：JQ8900
   语音识别模块：
*/

/*
   模块接线情况
   时钟源模块-DS307【SDA->21　 SCL->22】
   LM35D电子模拟温度传感器【analog－>34】
   显示模块－1.8寸串口屏【TXD->15(TXD);  RXD->14(RXD);   串口1重映射】　　
   语音播报模块－JQ8900【TXD->16(RX2);  RXD->17(TX2);   串口2】【Serial2.print】

*/

/*
   pro - processing
   alaclo - alarm_clock
   bri - brightness
*/

extern Ticker ticker1; //声明Ticker对象
extern Ticker ticker2; //声明Ticker对象

#define uchar unsigned char

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif                    //判断蓝牙是否已启用,没有的请运行并启用它








//变量表=======================================================//
//变量表=======================================================//
extern BluetoothSerial SerialBT; //定义蓝牙串口通讯名称
extern RTC_DS3231 rtc;
//网络相关
extern const char *ssid ;         //你的网络名称
extern const char *password ; //你的网络密码
extern const char *ntpServer ;
extern const long gmtOffset_sec; //对于东八区（UTC/GMT+08:00）来说该参数就需要填写 8 * 3600
extern const int daylightOffset_sec;    //如果使用夏令时 daylightOffset_sec 就填写3600，否则就填写0
extern char value_baoshi ;              //任意值
////显示相关///////////////////////////////////////////////////////////////////////////////////////
extern int val;
extern char buff[50]; // 显示屏模块缓存区
extern DateTime time_now;
extern char key_number;  //按键标识
extern uchar bri_value; // 10 - 最亮
extern bool sha_flag;
////温度相关///////////////////////
union Uion
{
    float temp;
    unsigned char temp_d[6];
};
extern Uion u;
////闹钟相关////////////////////////
extern char ala_xiang; //哪个闹钟响
extern char alarm_clock;   //闹钟设置模式：当前处于哪个闹钟
struct
{
    char t_hour;      //时
    char t_minute;    //分
    char model;       //模式(0 - 每天闹铃;1 - 工作日闹铃;2 - 单次闹铃;3 - 选定星期闹铃);
    char choo_day[8]; //选定星期闹铃下启用的日期
    bool ala_flag;    //是否启用
    bool ala_during;  //是否在响铃
                      //增加一个bool
} stru_alaclo[5] = {{0, 0, 0, "1234567", 1, 0},
                    {0, 0, 0, "1234567", 1, 0},
                    {0, 0, 0, "1234567", 1, 0},
                    {0, 0, 0, "1234567", 1, 0},
                    {0, 0, 0, "1234567", 1, 0}};
extern unsigned long previousMillis; //毫秒时间记录
extern const long  interval ;      //时间间隔
extern unsigned long currentMillis;      //读取当前时间
extern char call_num; //定时器中断函数2的计数个数
extern bool loop_flag; //主循环的运行标志（每秒打印一次）
extern String rev;
extern String reslurt;
extern String inString;
extern int y;
//变量表=======================================================//
//变量表=======================================================//
////按键相关///////////////////////////////////////////////////////////////////////////////////////
#define key_1 27
#define key_2 32
#define key_3 33
#define key_4 25
#define key_5 26
#define key_6 12


////函数///////////////////////////////////////////////////////////////////////////////////////
extern void IRAM_ATTR key_zd1(); //中断函数
extern void IRAM_ATTR key_zd2(); //中断函数
extern void IRAM_ATTR key_zd3(); //中断函数
extern void IRAM_ATTR key_zd4(); //中断函数
extern void IRAM_ATTR key_zd5(); //中断函数

extern void key_init();
extern void key_scan();
extern char *change_int(int num, char str[]);

extern void printLocalTime();

extern void adjust_time();

extern void keyvalue_read(); //从内部空间中读取数据

extern void keyvalue_write();

extern void display_main(bool flag=0); //主界面仅显示

extern void display_alaclo(bool flag = 0); //闹钟界面仅显示

extern void display_set(); //主界面-年 月 日 时 分钟设置

extern void display_set_ala(); //闹钟界面-时/分设置

extern void display_set_model(); //闹钟界面-模式设置

extern void display_set_choose(); //闹钟界面-自定义闹钟选定日期

extern void throb_time(uchar zt_size, uchar x, uchar y, char str_none[], char str_display[]); //目标位置闪烁函数

extern void baoshi(); //报时函数

extern void zd_baoshi(uchar num); //整点报时函数

extern void pro_ala(); //闹钟响铃处理函数

extern void key_pro(); //主界面的按键处理函数

extern void loop_alaclo(); //闹钟设置界面的循环处理函数

extern void callback1(); //回调函数

extern void callback2();

extern void core0code(void *parameter);

extern void adjest_N(String word);

extern void blu_set_ala(String word);//闹钟界面设置

extern void blu_set_hour(String word); //主界面-时 分钟设置

extern void blu_set_yee(String word); //主界面-时 分钟设置

#endif // ! __KEY_H
// #define __KEY_H
