/*
 * @Author: your name
 * @Date: 2022-03-06 11:45:31
 * @LastEditTime: 2022-03-06 15:14:30
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \4.WIFI开关\My_switch\My_switch.ino
 */
/*
 * @Author: your name
 * @Date: 2022-03-02 20:09:03
 * @LastEditTime: 2022-03-04 14:12:06
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \2.网络沙盒\wed_sabdbox.ino
 */
#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>
const char *SSID = "HiTV_602"; // wifi名称
const char *PASS = "13517812764";             // wifi密码
WebServer server(80);                      //声明WebServer对象
static const char FR_on[] = R"EOT(
<!DOCTYPE html>
<html>
<head> 
	<meta charset="utf-8"> 
	<title>菜鸟教程(runoob.com)</title> 
	<!格式：居中>
	<style>
		html { font-family: Helvetica; 
				display: inline-block;
				text-align: center;}
		.button { background-color: #4CAF50; 
					border: none; 
					color: white;
					padding: 16px 40px;
					text-decoration: none; 
					font-size: 30px; 
					margin: 2px; 
					cursor: pointer;}
		.button2{background-color:#555555;
					border: none; 
					color: white;
					padding: 16px 40px;
					text-decoration: none; 
					font-size: 30px; 
					margin: 2px; 
					cursor: pointer;}
	</style>
</head>
<body>
    <h1>ESP32网络服务器</h1>
    <p>GPIO 26 - State " ON "</p>
        <p>
            <a href="/off">
            <button class="button">ON</button>
            </a>
        </p>
</body>
</html>
)EOT";
static const char FR_off[] = R"EOT(
<!DOCTYPE html>
<html>
<head> 
	<meta charset="utf-8"> 
	<title>菜鸟教程(runoob.com)</title> 
	<!格式：居中>
	<style>
		html { font-family: Helvetica; 
				display: inline-block;
				text-align: center;}
		.button2{background-color:#555555;
					border: none; 
					color: white;
					padding: 16px 40px;
					text-decoration: none; 
					font-size: 30px; 
					margin: 2px; 
					cursor: pointer;}
	</style>
</head>
<body>
    <h1>ESP32网络服务器</h1>
    <p>GPIO 26 - State " ON "</p>
        <p>
            <a href="/on">
            <button class="button2">OFF</button>
            </a>
        </p>
</body>
</html>
)EOT";
void setup()
{
    Serial.begin(115200); //开始串口通讯
    Serial.println();
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
    Serial.print("/on");
    server.on("/on",
            HTTP_GET,
            []
            {
            server.setContentLength(sizeof(FR_on));
            server.send(200, "text/html");
            server.sendContent(FR_on, sizeof(FR_on)); });
    server.on("/off",
            HTTP_GET,
            []
            {
            server.setContentLength(sizeof(FR_off));
            server.send(200, "text/html");
            server.sendContent(FR_off, sizeof(FR_off)); });
    server.begin();
}
void loop()
{
    server.handleClient();
}
