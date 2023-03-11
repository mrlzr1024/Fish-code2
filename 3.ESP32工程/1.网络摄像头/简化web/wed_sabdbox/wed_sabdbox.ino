/*
 * @Author: your name
 * @Date: 2022-03-02 20:09:03
 * @LastEditTime: 2022-06-17 09:20:10
 * @LastEditors: MrLZR
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \2.网络沙盒\wed_sabdbox.ino
 */
#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>
const char *SSID = "Davinci";    // wifi名称
const char *PASS = "shiwoya132"; // wifi密码
WebServer server(80);            //声明WebServer对象

static auto hight_resolution = esp32cam::Resolution::find(800, 600);
void JpgHight()
{
    unsigned int* duffff;
    //设置分辨率
    if (!esp32cam::Camera.changeResolution(hight_resolution))
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
    //frame->toBmp();
    //server.send(200, "image/bmp");
    frame->writeTo(client);
    frame->writeTo(Serial);

}
void setup()
{
    Serial.begin(115200); //开始串口通讯
    Serial.println();
    /*启动相机*/
    {
        using namespace esp32cam;
        Config cfg; // camera configration
        cfg.setPins(pins::AiThinker);
        cfg.setResolution(hight_resolution);
        cfg.setBufferCount(2);
        cfg.setJpeg(80);
        if (Camera.begin(cfg))
        {
            Serial.println("开始设置香♂蕉");
        }
        else
        {
            Serial.println("香蕉设置♂失败");
        }
    }
    /*准备网络*/
    WiFi.persistent(false); //网络持续模式关闭
    WiFi.mode(WIFI_STA);    //工作站模式
    WiFi.begin(SSID, PASS);
    while (WiFi.status() != WL_CONNECTED)
        ;
    {
        delay(500);
    }
    Serial.print("登录：http://");
    Serial.print(WiFi.localIP());
    Serial.println("/cam");
    server.on("/cam", JpgHight);
    server.begin();
}
void loop()
{
    server.handleClient();
}
