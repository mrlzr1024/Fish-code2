/*
 * @Author: your name
 * @Date: 2022-03-02 20:09:03
 * @LastEditTime: 2022-03-12 11:33:21
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \2.网络沙盒\wed_sabdbox.ino
 */
//测试集：U20221211221000003099
#include <WebServer.h>
#include <WiFi.h>
#include "css.h"
const char *SSID = "Davinci";    // wifi名称
const char *PASS = "shiwoya132"; // wifi密码
WebServer server(80);            //声明WebServer对象
String data=" ";


IPAddress staticIP(192,168,43,178);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 0,1);




void setup()
{
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(115200); //开始串口通讯
  Serial.println();
  digitalWrite(3,HIGH);
  while (data[0] != 'U')
  {
    if (Serial.available()>0)
      data = Serial.readString();
    delay(100);
  }
  Serial.println("IN");
  /*准备网络*/
  Add(data);
  if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false) {
    Serial.println("Configuration failed.");
  }
  WiFi.persistent(false); //网络持续模式关闭
  WiFi.mode(WIFI_STA);    //工作站模式
  WiFi.begin(SSID, PASS);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  digitalWrite(4,HIGH);
  Serial.print("登录：http://");
  Serial.print(WiFi.localIP());
  server.on("/", HTTP_GET, []
            {
        server.setContentLength(sizeof(FR));
        server.send(200, "text/html");
        server.sendContent(FR, sizeof(FR)); });
  server.begin();
  data = " ";
}
void loop()
{
  if (Serial.available())
  {
    data = Serial.readString();
    if (data[0] == 'U')
    {
      Serial.println("OK");
      digitalWrite(5,HIGH);
      server.stop();
      Add(data);
      server.on("/", HTTP_GET, []
                {
        server.setContentLength(sizeof(FR));
        server.send(200, "text/html");
        server.sendContent(FR, sizeof(FR)); });
      server.begin();
      digitalWrite(5,LOW);
    }
  }
  server.handleClient();

  delay(1000);
}