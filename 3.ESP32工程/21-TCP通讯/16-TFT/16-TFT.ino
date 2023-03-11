/*
 * @Author: your name
 * @Date: 2022-04-30 17:38:41
 * @LastEditTime: 2022-05-02 16:15:12
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \18.-时钟\16-TFT.ino
 */
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <Arduino.h>
#include "doge.c"
#include <WiFi.h>

//=网络====================================================//
const char *ssid = "LAPTOP-AM3MI159 3568";
const char *password = "2&4238zO";
WiFiServer server; //声明服务器对象
//=网络====================================================//

TFT_eSPI tft = TFT_eSPI(); // 调用自定义库
int tmp = 0;
char x;
hw_timer_t *tim1 = NULL;
int tim1_IRQ_count = 0;
int Time = 0;
String rx_data, rx_data2;
void setup()
{
    //=串口====================================================//
    Serial.begin(115200);
    Serial2.begin(115200);
    //=串口====================================================//

    //=网络====================================================//
    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    // readBuff
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    server.begin(8080); //服务器启动监听端口号22333
    //=网络====================================================//

    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    tft.init();                //屏幕初始化
    tft.fillScreen(TFT_BLACK); //填充屏幕
    // 将字体颜色设置为白色，背景为黑色
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    // 将“光标”设置在显示屏的左上角（0,0），然后选择字体4
    tft.setCursor(0, 0, 1);
    tft.setTextSize(1);
    tft.setRotation(1);
    tft.setTextColor(TFT_CYAN);
    tft.print(tft.getCursorY());
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(14, tft.getCursorY());
    rx_data = "";
    rx_data2 = "";
}
void loop()
{
    char c;

    WiFiClient client = server.available(); //尝试建立客户对象
    if (client)                             //如果当前客户可用
    {
        Serial.println("[Client connected]");
        String readBuff;
        while (client.connected()) //如果客户端处于连接状态
        {
            if (client.available()) //如果有可读数据
            {
                c = client.read(); //读取一个字节
                                        //也可以用readLine()等其他方法
                client.print(c);
                Serial2.print(c);
                tft.print(c);
            }
            while (Serial2.available() > 0) // 判断串口是否有数据
            {
                x = Serial2.read(); //读取串口值
                if (tft.getCursorX() >= 156)
                {
                    tft.setCursor(14, tft.getCursorY() + 8);
                }
                if (tft.getCursorY() > 120)
                {
                    tft.setCursor(0, 0, 1);
                    tft.fillScreen(TFT_BLACK); //填充屏幕
                    tft.setTextColor(TFT_CYAN);
                    tft.print(tft.getCursorY());
                    tft.setTextColor(TFT_GREEN);
                    tft.setCursor(14, tft.getCursorY());
                }
                tft.setTextColor(TFT_GREEN);
                tft.print(x);
                rx_data2 += x;
                if (x == '\n')
                {
                    tft.setTextColor(TFT_CYAN);
                    tft.print(tft.getCursorY() / 8);
                    tft.setTextColor(TFT_GREEN);
                    tft.setCursor(14, tft.getCursorY());
                    client.print(rx_data2);
                    //Serial.print(rx_data2);
                    rx_data2 = "";
                }
            }
            // client.stop(); //结束当前连接:
            // Serial.println("[Client disconnected]");
        }

        ////////////////////////////////////////////////////
    }
}

//  void serialEvent()
// {
//   rx_data="";
//   while (Serial2.available())
//   {
//     rx_data += char(Serial2.read());
//     delay(2); //这里不能去掉，要给串口处理数据的时间
//   }
//   Serial2.println(rx_data);
// }
// void tim1Interrupt()
// { //中断服务函数
//   Time++;
// }

//====================================================================//
// #include <WiFi.h>

// const char *ssid = "LAPTOP-AM3MI159 3568";
// const char *password = "2&4238zO";

// WiFiServer server; //声明服务器对象

// void setup()
// {
//     Serial.begin(115200);
//     Serial.println();

//     WiFi.mode(WIFI_STA);
//     WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(".");
//     }
//     Serial.println("Connected");
//     Serial.print("IP Address:");
//     Serial.println(WiFi.localIP());

//     server.begin(22333); //服务器启动监听端口号22333
// }

// void loop()
// {
//     WiFiClient client = server.available(); //尝试建立客户对象
//     if (client) //如果当前客户可用
//     {
//         Serial.println("[Client connected]");
//         String readBuff;
//         while (client.connected()) //如果客户端处于连接状态
//         {
//             if (client.available()) //如果有可读数据
//             {
//                 char c = client.read(); //读取一个字节
//                                         //也可以用readLine()等其他方法
//                 readBuff += c;
//                 if(c == '\r') //接收到回车符
//                 {
//                     client.print("Received: " + readBuff); //向客户端发送
//                     Serial.println("Received: " + readBuff); //从串口打印
//                     readBuff = "";
//                     break; //跳出循环
//                 }
//             }
//         }
//         client.stop(); //结束当前连接:
//         Serial.println("[Client disconnected]");
//     }
// }
