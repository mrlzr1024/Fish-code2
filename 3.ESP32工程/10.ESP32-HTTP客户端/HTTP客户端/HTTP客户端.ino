/*
 * @Author: your name
 * @Date: 2022-03-11 13:35:15
 * @LastEditTime: 2022-03-11 22:43:38
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \9.ESP-IDF实验e:\咸鱼先生的单片机开发文件\3.ESP32工程\10.ESP32-HTTP客户端\HTTP客户端.ino
 */
#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "GUET-WiFi"    //网络名称
const char *password = "" //网络密码

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  HTTPClient http; // 声明HTTPClient对象

  http.begin("http://example.com/index.html"); // 准备启用连接

  int httpCode = http.GET(); // 发起GET请求

  if (httpCode > 0) // 如果状态码大于0说明请求过程无异常
  {
    if (httpCode == HTTP_CODE_OK) // 请求被服务器正常响应，等同于httpCode == 200
    {
      String payload = http.getString(); // 读取服务器返回的响应正文数据
                                         // 如果正文数据很多该方法会占用很大的内存
      Serial.println(payload);
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end(); // 结束当前连接

  delay(10000);
}
