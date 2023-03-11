#include "My_Network.h"

// const char *ssid = "Davinci";        // WIFI账户
// const char *password = "shiwoya132"; // WIFI密码

// bool Wlan_init()
// {
//     // Serial.begin(115200);
//     Serial.println();
//     Serial.print("目标网络SSID: ");
//     Serial.println(ssid);
//     if (!WiFi.isConnected())
//     {
//         WiFi.begin(ssid, password);
//         for (uint8_t t = 4; t > 0; t--)
//         {
//             Serial.printf("[启动] 倒数计时 %d...\n", t); //后期显示在OLED
//             Serial.flush();
//             delay(100);
//         }
//         while (WiFi.status() != WL_CONNECTED && digitalRead(0) == HIGH)
//         {
//             Serial.print(".");
//             // wait 1 second for re-trying
//             delay(100);
//         }
//         if (digitalRead(0) == LOW)
//         {
//             Serial.print("连接失败");
//             return false;
//         }
//         Serial.print("连接至目标网络");
//         return true;
//     }
//     else
//     {
//         Serial.print("连接至目标网络");
//         return true;
//     }
// }