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
//关键一----参数抓取：arg() —— 获取请求参数的值
//<!关键二---HTML----fetch()发出HTTP请求>
static char FR_init[] = R"EOT(<html>
  <head>
    <title>ESP32-CAM Robot</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
  </head>
  <body>
    <h1>ESP32-CAM Pan and Tilt</h1>
    <img src="/cam" id="photo" >
    <table>
      <tr><td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('up');" ontouchstart="toggleCheckbox('up');">Up</button></td></tr>
      <tr><td align="center">
      <button class="button" onmousedown="toggleCheckbox('left');" ontouchstart="toggleCheckbox('left');">Left</button></td>
      <td align="center">
      </td>
      <td align="center">
      <button class="button" onmousedown="toggleCheckbox('right');" ontouchstart="toggleCheckbox('right');">Right</button></td>
    </tr>
      <tr><td colspan="3" align="center"><button class="button" onmousedown="toggleCheckbox('down');" ontouchstart="toggleCheckbox('down');">Down</button></td></tr>                   
    </table>
   <script>
   function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/action?go=" + x, true);
     xhr.send();
   }
   window.onload = document.getElementById("photo").src = window.location.href.slice(0, -1) + ":80/cam";
  </script>
  </body>
</html>)EOT";

/*=============================================================================*/
/*=============================================================================*/

void Server_web()
{
  /*=============================================================================*/
  server.on("/action",
            HTTP_GET,
            [] { // Insert(FR_init,FR_on,626);
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              // digitalWrite(output, HIGH);
              Serial.println("LED ON");
              Serial.print("var=");
              Serial.println(server.arg("var"));
              //关键一----参数抓取：arg() —— 获取请求参数的值
            });
  /*=============================================================================*/
  server.on("/off",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              // digitalWrite(output, HIGH);
              Serial.println("LED OFF");
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
              Serial.println("left");
              Serial.print("val=");
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
              Serial.println("right");
              Serial.print("val=");
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
              Serial.println("forward");
              Serial.print("val=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/back",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              // server.sendContent(FR_init, sizeof(FR_init));
              // digitalWrite(output, HIGH);
              Serial.println("back");
              Serial.print("val=");
              Serial.println(server.arg("val"));
            });
  /*=============================================================================*/
  server.on("/",
            HTTP_GET,
            []
            {
              server.setContentLength(sizeof(FR_init));
              server.send(200, "text/html");
              server.sendContent(FR_init, sizeof(FR_init));
              Serial.println("OK");
            });
}
void setup()
{
  pinMode(output, OUTPUT);
  Camera_Init();

  //设置初始值为低电平
  digitalWrite(output, LOW);
  Server_web();
  server.begin();
}
void loop()
{

  server.handleClient();
}
