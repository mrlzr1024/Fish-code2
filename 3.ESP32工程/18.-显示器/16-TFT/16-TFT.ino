/*
 * @Author: your name
 * @Date: 2022-04-30 17:38:41
 * @LastEditTime: 2022-05-02 16:15:12
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \18.-时钟\16-TFT.ino
 */
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <Arduino.h>
#include "doge.c"
TFT_eSPI tft = TFT_eSPI(); // 调用自定义库
int tmp = 0;
char x;
hw_timer_t *tim1 = NULL;
int tim1_IRQ_count = 0;
int Time = 0;
String rx_data, rx_data2;
void setup()
{

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  tft.init();                //屏幕初始化
  tft.fillScreen(TFT_BLACK); //填充屏幕
  // 将字体颜色设置为白色，背景为黑色
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  // 将“光标”设置在显示屏的左上角（0,0），然后选择字体4
  tft.setCursor(0, 0, 1);
  tft.setTextSize(1);
  // tft.fillRect(0, 0, 128, 160, TFT_BLACK);
  // tft.setRotation(4);
  // tft.println("NanNing");
  // tft.setTextFont(1);
  // tft.println("Beijing");
  // tft.setTextFont(2);
  // tft.println("Shanghai");
  // tft.setTextFont(9);
  tft.setRotation(1);
  // tim1 = timerBegin(0, 80, true);
  // timerAttachInterrupt(tim1, tim1Interrupt, true);
  // timerAlarmWrite(tim1, 1000000ul, true);
  // timerAlarmEnable(tim1);
  tft.setTextColor(TFT_CYAN);
  tft.print(tft.getCursorY());
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(14, tft.getCursorY());
  rx_data = "";
  rx_data2 = "";
}

void loop()
{

  // put your main code here, to run repeatedly:
  tmp = touchRead(T0);
  while (Serial.available() > 0) // 判断串口是否有数据
  {
    x = Serial.read(); //读取串口值
    if (tft.getCursorY() > 120)
    {
      tft.setCursor(0, 0, 1);
      tft.fillScreen(TFT_BLACK); //填充屏幕
      tft.setTextColor(TFT_CYAN);
      tft.print(tft.getCursorY());
      tft.setTextColor(TFT_GREEN);
      tft.setCursor(14, tft.getCursorY());
    }
    tft.setTextColor(TFT_GOLD);
    tft.print(x);
    rx_data += x;
    if(rx_data=="clear"){
      tft.setCursor(0, 0, 1);
      tft.fillScreen(TFT_BLACK); //填充屏幕
    }
    if (x == '\n')
    {
      tft.setTextColor(TFT_CYAN);
      tft.print(tft.getCursorY() / 8);
      tft.setTextColor(TFT_GREEN);
      tft.setCursor(14, tft.getCursorY());
      Serial2.print(rx_data);
      rx_data = "";
    }
  }
  while (Serial2.available() > 0) // 判断串口是否有数据
  {
    x = Serial2.read(); //读取串口值
    if(tft.getCursorX()>=156){
      tft.setCursor(14, tft.getCursorY()+8);
    }
    if (tft.getCursorY() > 120)
    {
      tft.setCursor(0, 0, 1);
      tft.fillScreen(TFT_BLACK); //填充屏幕
      tft.setTextColor(TFT_CYAN);
      tft.print(tft.getCursorY());
      tft.setTextColor(TFT_GREEN);
      tft.setCursor(14, tft.getCursorY());
    }
    tft.setTextColor(TFT_GREEN);
    tft.print(x);
    rx_data2 += x;
    // if(strstr(rx_data2.c_str(),"[1;32")){
    //   tft.setTextColor(TFT_BLUE);
    // }
    // else if(x=='['){
    //   tft.setTextColor(TFT_GREEN);
    // }
    if (x == '\n')
    {
      tft.setTextColor(TFT_CYAN);
      tft.print(tft.getCursorY() / 8);
      tft.setTextColor(TFT_GREEN);
      tft.setCursor(14, tft.getCursorY());
      Serial.print(rx_data2);
      rx_data2 = "";
    }
    ////////////////////////////////////////////////////
  }
}
//  void serialEvent()
// {
//   rx_data="";
//   while (Serial2.available())
//   {
//     rx_data += char(Serial2.read());
//     delay(2); //这里不能去掉，要给串口处理数据的时间
//   }
//   Serial2.println(rx_data);
// }
// void tim1Interrupt()
// { //中断服务函数
//   Time++;
// }
