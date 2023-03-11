/*
   @Author: your name
   @Date: 2022-02-16 11:51:19
 * @LastEditTime: 2022-03-03 08:14:55
 * @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \1.网络摄像头\web.ino
*/
#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>

const char *WIFI_SSID = "LAPTOP-AM3MI159 3568"; // 改成自己的wifi名称
const char *WIFI_PASS = "2&4238zO";             // 改成自己的wifi密码

WebServer server(80); //声明WebServer对象

/*分辨率定义*/
// static auto loRes = esp32cam::Resolution::find(320, 240); //高分辨率
static auto hiRes = esp32cam::Resolution::find(800, 600); //低分辨率
/*====输出JPG====*/
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes))
  { //如果设置高分辨率失败
    Serial.println("SET-HI-RES FAIL");
  }
  auto frame = esp32cam::capture(); //获取图像，获取的图像格式为JPG
  if (frame == nullptr)
  {
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));

  server.setContentLength(frame->size());
  server.send(200, "image/jpeg");
  WiFiClient client = server.client();
  frame->writeTo(client);
}
/*获取视频流信息*/
/*===输出视频===*/
void handleMjpeg()
{
  if (!esp32cam::Camera.changeResolution(hiRes))
  { //如果设置高分辨率失败
    Serial.println("SET-HI-RES FAIL");
  }

  Serial.println("STREAM BEGIN");
  WiFiClient client = server.client();            // 建立WiFi客户端对象
  auto startTime = millis();                      //返回当前程序时的毫秒数
  int res = esp32cam::Camera.streamMjpeg(client); //向WiFi客户端发送视频流信息并返回全局帧数
  if (res <= 0)
  { //若帧数小于0
    Serial.printf("STREAM ERROR %d\n", res);
    return;
  }
  auto duration = millis() - startTime;                                       //全局时间
  Serial.printf("STREAM END %dfrm %0.2ffps\n", res, 1000.0 * res / duration); // fps=全局帧数除以全局时间
}
void setup()
{
  Serial.begin(115200); //开始串口通讯
  Serial.println();

  { //启动相机
    using namespace esp32cam;
    Config cfg;
    cfg.setPins(pins::AiThinker);
    cfg.setResolution(hiRes);
    cfg.setBufferCount(4);//渲染
    cfg.setJpeg(80); 
    bool ok = Camera.begin(cfg);
    Serial.println(ok ? "CAMERA OK" : "CAMERA FAIL");
  }
  //启动网络
  WiFi.persistent(false);
  WiFi.mode(WIFI_STA); //工作站模式
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Serial.print("登录：http://");
  Serial.print(WiFi.localIP());
  Serial.println("/cam-hi.jpg");
  Serial.println("/cam.mjpeg");
  server.on("/cam.mjpeg", handleMjpeg);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.begin();
}

void loop()
{
  server.handleClient();
}
