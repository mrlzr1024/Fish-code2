/*
   @Author: your name
   @Date: 2022-04-12 22:32:10
   @LastEditTime: 2022-04-13 13:22:40
   @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \esp32cam_car\esp32cam_car.ino
*/
/**
   ESP32 HTTP GET方式获取网络数据


*/

#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

//填写WIFI入网信息
const char *ssid = "Davinci";        // WIFI账户
const char *password = "shiwoya132"; // WIFI密码
void setup()
{

  Serial.begin(115200);
  Serial.println();

  pinMode(4, OUTPUT);
  pinMode(33, OUTPUT);
  Serial.print("目标网络SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  for (uint8_t t = 4; t > 0; t--)
  {
    Serial.printf("[启动] 倒数计时 %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  digitalWrite(33, HIGH);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
  }
  Serial.print("连接至目标网络");
  digitalWrite(33, LOW);
  for (int i = 0; i < 5; i++) {
    digitalWrite(4, HIGH);
    delay(10);
    digitalWrite(4, LOW);
    delay(10);
  }
  /* 开始访问指定服务器地址，获取数据  */
  Serial.print("连接至： ");
  Serial.println(ssid);
  HTTPClient http;

  http.begin("http://news.baidu.com/"); //访问服务器地址


  int httpCode = http.GET();


  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] 获取到的字节数为: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] 获取... 失败： %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop()
{
  delay(5000);
}
