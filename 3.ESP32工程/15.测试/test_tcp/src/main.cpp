#include <WiFi.h>
#include <WebServer.h>

WebServer esp32_server(80); //声明一个 WebServer 的对象，对象的名称为 esp32_server
                            //设置网络服务器响应HTTP请求的端口号为 80

const char *ssid = "HiTV_602";        // wifi名
const char *password = "13517812764"; // wifi密码

void handleRoot() //该函数内为处理网站根目录 “/” 时所执行的内容
{
    Serial.print("客户端访问！");
    esp32_server.send(200, "text/plain", "Holle World!"); //用函数 send 向浏览器发送信息，200表示正常状态码，text/plain表示发送的内容为纯文本类型 text/html为HTML的网页信息，"Holle World!"为发送的内容
}

void handleFound()
{
    esp32_server.send(404, "text/plain", "404:Not Found!"); //用函数 send 向浏览器发送信息，404表示服务器上找不到请求的资源，text/plain表示发送的内容为纯文本类型，"404：Not Found!"为发送的内容
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200); //初始化串口通信并设置波特率为115200

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());

    esp32_server.begin();                                 //启动网络服务器
    esp32_server.on("/", HTTP_GET, handleRoot); //函数处理当有HTTP请求 "/" 时执行函数 handleRoot
    esp32_server.onNotFound(handleFound);                 //当请求的网络资源不在服务器的时候，执行函数 handleFound
}
void loop()
{
    // put your main code here, to run repeatedly:
    esp32_server.handleClient();
}
