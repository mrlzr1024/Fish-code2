#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include "GUET.c"
TFT_eSPI tft = TFT_eSPI(); // 调用自定义库
int tmp = 0;
void setup()
{

  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  tft.init(); //屏幕初始化
  // tft.set_size(128,160);
  tft.fillScreen(TFT_BLACK); //填充屏幕
  // tft.fillRect(0,0,240,320,TFT_RED);
  // 将字体颜色设置为白色，背景为黑色
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  // 将“光标”设置在显示屏的左上角（0,0），然后选择字体4
  tft.setCursor(0, 0, 4);

  tft.setTextSize(1);

  // tft.fillRect(0, 0, 128, 160, TFT_BLACK);
  // tft.setRotation(1);

  // tft.println("NanNing");
  // tft.setTextFont(1);
  // tft.println("Beijing");
  // tft.setTextFont(2);
  // tft.println("Shanghai");
  // tft.setTextFont(9);
  tft.setRotation(2);
  tft.setSwapBytes(true);
  tft.pushImage(0, 0, 120, 160,gImage_GUET);
}

void loop()
{

  // put your main code here, to run repeatedly:
  // tmp = touchRead(T0);
  // if (tmp < 30)
  // {
  //   delay(50);
  //   tmp = touchRead(T0);
  //   if (tmp < 30)
  //   {
  //     digitalWrite(2, LOW);
  //     tft.fillScreen(TFT_BLACK); //填充屏幕
  //   }
  // } // Touch0 通道是 GPIO 4.

  // else
  // { // get value of Touch 0 pin = GPIO 4
  //   digitalWrite(2, HIGH);
  //   tft.setCursor(0, 0, 4);
  //   tft.println("NanNing");
  // }
  // delay(50);
}
