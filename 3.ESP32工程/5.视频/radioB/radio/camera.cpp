/*
 * @Author: your name
 * @Date: 2022-03-07 16:22:01
 * @LastEditTime: 2022-06-02 20:36:28
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \5.视频\radio.ino
 */
#include "camera.hpp"
const char *SSID = "Davinci";    // wifi名称
const char *PASS = "shiwoya132"; // wifi密码
WebServer server(80);            //声明WebServer对象
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

//将图片打印到串口
void Print_jpg()
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
    frame->writeTo(Serial);
}
/*获取视频流信息*/
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
/*bmp*/
static void wantBmp()
{
    auto frame = esp32cam::capture();
    if (frame == nullptr)
    {
        Serial.println("capture() failure");
        server.send(500, "text/plain", "still capture error\n");
        return;
    }
    // Serial.printf("capture() success: %dx%d %zub\n", frame->getWidth(), frame->getHeight(), frame->size());

    if (!frame->toBmp())
    {
        Serial.println("toBmp() failure");
        server.send(500, "text/plain", "convert to BMP error\n");
        return;
    }
    Serial.printf("toBmp() 成功了: %dx%d %zub\n", frame->getWidth(), frame->getHeight(), frame->size());

    server.setContentLength(frame->size());
    // server.send(200, wantBmp ? "image/bmp" : "image/jpeg");
    server.send(200, "image/bmp");
    WiFiClient client = server.client();
    frame->writeTo(client);
    Serial.println("=======================================================================");
    frame->writeTo(Serial);
    Serial.println("=======================================================================");
}

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
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA); //工作站模式
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }
    Serial.print("登录:http://");
    Serial.print(WiFi.localIP());
    server.on("/cam", handleMjpeg);
    server.on("/jpg", JpgHight);
    server.on("/j", Print_jpg);
    server.on("/bmp", wantBmp);
}
