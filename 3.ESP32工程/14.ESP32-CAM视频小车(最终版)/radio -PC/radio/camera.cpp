/*
   @Author: your name
   @Date: 2022-03-07 16:22:01
 * @LastEditTime: 2022-04-13 13:01:40
 * @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \5.视频\radio.ino
*/
#include "camera.hpp"
const char *SSID = "LAPTOP-AM3MI159 3568"; // wifi名称
const char *PASS = "2&4238zO";             // wifi密码
WebServer server(80);                      //声明WebServer对象
/*分辨率定义*/
static auto loRes = esp32cam::Resolution::find(320, 240); //高分辨率
static auto hiRes = esp32cam::Resolution::find(800, 600); //低分辨率

void JpgHight()
{
  //设置分辨率
  if (!esp32cam::Camera.changeResolution(hiRes))
  { //如果设置高分辨率失败
    Serial.println("高分辨率设置失败");
  }
  //获取图像
  auto frame = esp32cam::capture();
  if (frame == nullptr)
  {
    Serial.println("分辨率设置不彳亍 ");
    server.send(503, "", "");
    return;
  }
  server.setContentLength(frame->size());
  WiFiClient client = server.client();
  server.send(200, "image/jpeg");
  frame->writeTo(client);
}
void Jpg_test()
{
  //设置分辨率
  if (!esp32cam::Camera.changeResolution(hiRes))
  { //如果设置高分辨率失败
    Serial.println("高分辨率设置失败");
  }
  //获取图像
  auto frame = esp32cam::capture();
  if (frame == nullptr)
  {
    Serial.println("分辨率设置不彳亍 ");
    server.send(503, "", "");
    return;
  }
  server.setContentLength(frame->size());
  WiFiClient client = server.client();
  server.send(200, "image/jpeg");
  while (1)
  {
    frame->writeTo(client);
    frame = esp32cam::capture();
  }
}

/*获取视频流信息*/
void handleMjpeg()
{
  if (!esp32cam::Camera.changeResolution(hiRes))
  { //如果设置高分辨率失败
    Serial.println("SET-HI-RES FAIL");
  }
  // Serial.println("STREAM BEGIN");
  WiFiClient client = server.client();            // 建立WiFi客户端对象
  auto startTime = millis();                      //返回当前程序时的毫秒数
  int res = esp32cam::Camera.streamMjpeg(client); //向WiFi客户端发送视频流信息并返回全局帧数
  if (res <= 0)
  { //若帧数小于0
    // Serial.printf("STREAM ERROR %d\n", res);
    return;
  }
  auto duration = millis() - startTime; //全局时间

  // Serial.printf("STREAM END %dfrm %0.2ffps\n", res, 1000.0 * res / duration); // fps=全局帧数除以全局时间
}
/*创建网络属性*/
IPAddress staticIP(192,168,137,253);
IPAddress gateway(192,168,137,1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(192,168,137,1);
IPAddress dns2(0,0,0,0);
void Camera_Init()
{
  Serial.begin(115200); //开始串口通讯
  Serial.println();
  {
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(2);
    cfg.setJpeg(80);
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  //if (WiFi.config(staticIP, gateway, subnet, dns1, dns2) == false) {
    //Serial.println("Configuration failed.");
  //}

  //WiFi.persistent(false);
  WiFi.mode(WIFI_STA); //工作站模式
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(4, HIGH);
    delay(5);
    digitalWrite(4, LOW);
    delay(5);
  }
  Serial.print("登录:http://");
  Serial.println(WiFi.localIP());
  // IP地址
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  //子网掩码
  Serial.print("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  //网关地址
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
  // DNS
  Serial.print("DNS 1: ");
  Serial.println(WiFi.dnsIP(0));
  Serial.print("DNS 2: ");
  Serial.println(WiFi.dnsIP(1));
  server.on("/cam", handleMjpeg);
  server.on("/jpg", JpgHight);
  server.on("/test", Jpg_test);
}
