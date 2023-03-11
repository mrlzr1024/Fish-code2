/*
 * @Author: your name
 * @Date: 2022-03-02 20:09:03
 * @LastEditTime: 2022-03-12 11:33:21
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \2.网络沙盒\wed_sabdbox.ino
 */
#include <WebServer.h>
#include <WiFi.h>
const char *SSID = "GUET-WiFi";    // wifi名称
const char *PASS = " "; // wifi密码
WebServer server(80);            //声明WebServer对象
static const char FR[] = R"rawliteral(<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Mr.LZR(runoob.com)</title>
const xhr = new XMLHttpRequest()
</head>
<body>
<table>
                 <tr><td></td><td align="center">
                  <button class="button button2" id="backward" onclick=" fetch(document.location.origin+'/val');xhr.send("201")">REVERSE</button></td><td></td></tr>
                  </table>
<h1>我的第一个标题</h1>
<p>我的第一个段落。</p>

</body>
</html>)rawliteral";
void setup()
{
  Serial.begin(115200); //开始串口通讯
  Serial.println();
  /*准备网络*/
  WiFi.persistent(false); //网络持续模式关闭
  WiFi.mode(WIFI_STA);    //工作站模式
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.print("登录：http://");
  Serial.print(WiFi.localIP());
  server.on("/", HTTP_GET, []
            {
        server.setContentLength(sizeof(FR));
        server.send(200, "text/html");
        server.sendContent(FR, sizeof(FR)); });
  server.begin();
}
void loop()
{
  Serial.print("循环中.......");
  server.handleClient();
  Serial.println(server.hostHeader());
  Serial.println(server.headerName(0));
  delay(1000);
}
