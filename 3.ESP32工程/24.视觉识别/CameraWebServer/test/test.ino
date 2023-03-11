#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>

const char* WIFI_SSID = "LAPTOP-AM3MI159 3568";  // 改成自己的wifi名称
const char* WIFI_PASS = "2&4238zO";  // 改成自己的wifi密码

WebServer server(80);//声明WebServer对象

/*分辨率定义*/
static auto loRes = esp32cam::Resolution::find(320, 240);//高分辨率
static auto hiRes = esp32cam::Resolution::find(800, 600);//低分辨率
/*====输出BMP====*/
void handleBmp()
{
  /*设置分辨率*/
  if (!esp32cam::Camera.changeResolution(loRes)) {
    Serial.println("SET-LO-RES FAIL");//设置低分辨率失败
  }
  /*获取图像*/
  auto frame = esp32cam::capture();//拍照 capture，获取的图像格式为JPG
  if (frame == nullptr) {//如果没有拍成功
    Serial.println("CAPTURE FAIL");
    server.send(503, "", "");//web服务器不能处理HTTP请求==503
    return;
  }
  Serial.printf("CAPTURE OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));//如果拍成功，则向串口打印长，宽，大小
  /*转为BMP*/
  if (!frame->toBmp()) {//如果图像没有被转化为BMP
    Serial.println("CONVERT FAIL");//打印[转换失败]
    server.send(503, "", "");//web服务器不能处理HTTP请求==503
    return;
  }
  Serial.printf("CONVERT OK %dx%d %db\n", frame->getWidth(), frame->getHeight(),
                static_cast<int>(frame->size()));//如果转化成功，则向串口打印长，宽，大小
  /*发到从机*/
  server.setContentLength(frame->size());//设置内容长度
  server.send(200, "image/bmp");//成功处理了请求，一般情况下都是返回此状态码； ==200
  WiFiClient client = server.client();
  frame->writeTo(client);//写到从机
}

void serveJpg()//获取的图像格式为JPG
{
  auto frame = esp32cam::capture();//获取图像，获取的图像格式为JPG
  if (frame == nullptr) {
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
/*====设置输出JPG低分辨率====*/
void handleJpgLo()
{
  if (!esp32cam::Camera.changeResolution(loRes)) {//如果设置低分辨率失败
    Serial.println("SET-LO-RES FAIL");
  }
  serveJpg();
}
/*====设置输出JPG高分辨率====*/
void handleJpgHi()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {//如果设置高分辨率失败
    Serial.println("SET-HI-RES FAIL");
  }
  serveJpg();
}

void handleJpg()
{
  server.sendHeader("Location", "/cam-hi.jpg");
  server.send(302, "", "");
}
/*获取视频流信息*/
void handleMjpeg()
{
  if (!esp32cam::Camera.changeResolution(hiRes)) {//如果设置高分辨率失败
    Serial.println("SET-HI-RES FAIL");
  }

  Serial.println("STREAM BEGIN");
  WiFiClient client = server.client();// 建立WiFi客户端对象
  auto startTime = millis();//返回当前程序时的毫秒数
  int res = esp32cam::Camera.streamMjpeg(client);//向WiFi客户端发送视频流信息并返回全局帧数
  if (res <= 0) {//若帧数小于0
    Serial.printf("STREAM ERROR %d\n", res);
    return;
  }
  auto duration = millis() - startTime;//全局时间
  Serial.printf("STREAM END %dfrm %0.2ffps\n", res, 1000.0 * res / duration);//fps=全局帧数除以全局时间
}

void setup()
{
  Serial.begin(115200);//开始串口通讯
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

  WiFi.persistent(false);
  WiFi.mode(WIFI_STA);//工作站模式
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("  /cam.bmp");
  Serial.println("  /cam-lo.jpg");
  Serial.println("  /cam-hi.jpg");
  Serial.println("  /cam.mjpeg");

  server.on("/cam.bmp", handleBmp);
  server.on("/cam-lo.jpg", handleJpgLo);
  server.on("/cam-hi.jpg", handleJpgHi);
  server.on("/cam.jpg", handleJpg);
  server.on("/cam.mjpeg", handleMjpeg);

  server.begin();
}

void loop()
{
  server.handleClient();
}
