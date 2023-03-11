#include "tcp.h"

// const char *ssid = "HiTV_602";        // wifi名
// const char *password = "13517812764"; // wifi密码
const char *ssid = "Davinci";        // wifi名
const char *password = "shiwoya132"; // wifi密码

// WiFiServer server; //声明服务器对象
WiFiClient client; //声明一个客户端对象，用于与服务器进行连接

void connect_tcp(void *parameter);

void Task_init()
{
    WiFi.mode(WIFI_STA);  //站点模式
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(2500);
        Serial.print(".");
    }
    Serial.println("已连接");
    Serial.print("本机ip地址:");
    Serial.println(WiFi.localIP());

    Serial.println("尝试访问服务器");

    xTaskCreate(
        connect_tcp, /* Task function. */
        "TaskTwo",   /* String with name of task. */
        10000,       /* Stack size in bytes. */
        NULL,        /* Parameter passed as input of the task */
        1,           /* Priority of the task. */
        NULL);       /* Task handle. */
}
String readBuff, cmd;
void connect_tcp(void *parameter)
{
    while (1)
    {
        if (client.connect("free.svipss.top", 38781)) //尝试访问目标地址
        {
            Serial.println("尝试访问");

            client.print("Connected!"); //向服务器发送“hello world”
            while (client.connected())    //如果处于连接状态
            {
                if (client.available())
                {
                    Serial.println("查询信息:");
                    if (client.available()) //如果有数据可读取
                    {
                        String line = client.readStringUntil('\n'); //读取数据到换行符
                        Serial.print("收到消息：");
                        Serial.println(line);
                        client.write(line.c_str()); //将收到的数据回发
                        cmd=line;
                        // c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同
                    }
                }
            }
            // Serial.println("关闭当前连接");
            // client.stop(); //关闭客户端
        }
        delay(100);
    }
}