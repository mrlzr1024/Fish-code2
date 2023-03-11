/*
   @Author: your name
   @Date: 2022-03-06 11:45:31
 * @LastEditTime: 2022-03-24 19:54:49
 * @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \4.WIFI开关\My_switch\My_switch.ino
*/
/*
   @Author: your name
   @Date: 2022-03-02 20:09:03
   @LastEditTime: 2022-03-04 14:12:06
   @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \2.网络沙盒\wed_sabdbox.ino
*/
#include "camera.hpp"
const int output = 4;
const int warning = 33;
//关键一----参数抓取：arg() —— 获取请求参数的值
//<!关键二---HTML----fetch()发出HTTP请求>
static char FR_init[] = R"EOT(<html>
<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <title>ESP32 CAM Robot</title>
    </head>
    <body>
    </body>
</html>)EOT";

/*=============================================================================*/
/*=============================================================================*/

void Server_web()
{
  /*=============================================================================*/
  server.on("/on",
            HTTP_GET,
            [] { // Insert(FR_init,FR_on,626);
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              Serial.println("LED ON");
             digitalWrite(output, HIGH);
              //关键一----参数抓取：arg() —— 获取请求参数的值
            });
  /*=============================================================================*/
  server.on("/off",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              Serial.println("LED OFF");
              digitalWrite(output, LOW);
            });
  /*=============================================================================*/
  server.on("/left",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              // digitalWrite(output, HIGH);
              Serial.print("l=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/right",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              // digitalWrite(output, HIGH);
              Serial.print("r=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/up",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              // digitalWrite(output, HIGH);
              Serial.print("f=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/back",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              Serial.print("b=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/deviation",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              Serial.print("d=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/stop",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              Serial.println("s");
            });
  /*=============================================================================*/
  server.on("/",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              Serial.println("OK");
            });
}
void setup()
{
  pinMode(output, OUTPUT);
  pinMode(warning, OUTPUT);
  Camera_Init();

  //设置初始值为低电平
  digitalWrite(output, LOW);
  digitalWrite(warning, HIGH);
  Server_web();
  server.begin();
}
void loop()
{

  server.handleClient();
}
