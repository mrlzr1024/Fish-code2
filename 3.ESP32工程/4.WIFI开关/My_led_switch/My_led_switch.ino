/*
   @Author: your name
   @Date: 2022-03-06 11:45:31
   @LastEditTime: 2022-03-06 20:11:42
   @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \4.WIFI开关\My_switch\My_switch.ino
*/
/*
   @Author: your name
   @Date: 2022-03-02 20:09:03
   @LastEditTime: 2022-03-04 14:12:06
   @LastEditors: Please set LastEditors
   @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
   @FilePath: \2.网络沙盒\wed_sabdbox.ino
*/
#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>
const char *QSSID = "Davinci"; // wifi名称
const char *PASSw = "shiwoya132";             // wifi密码
const int output = 4;
WebServer server(80);                      //声明WebServer对象
//HTML框架修改位置：629(索引)
static  char FR_init[] = R"EOT(<html>
<head>
	<meta charset="utf-8">
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
</body>
</html>)EOT";
static  char FR_on[] = R"EOT(|LZR|<p>GPIO 14 - State " ON "</p>
<p>
<a href = "/off">
<button class = "button">ON</button>
</a>
</p>)EOT";
static  char FR_off[] = R"EOT(|LZR|<p>GPIO 14 - State " OFF "</p>
<p>
<a href = "/on">
<button class = "button">OFF</button>
</a>
</p>)EOT";
char C[1000];
//插入函数 A:主数组 B：从数组 in:要插入位置A的索引
int Insert( char* A,  char* B, int in) {
  int i = 0;

  if (in > strlen(A)) {
    return 0;
  }
  for (int j = 0; j <= in; j++) {
    C[j] = A[j];
  }
  for (int j = in + 1; j <= in + strlen(B); j++) {
    C[j] = B[j - in - 1];
  }
  for (int j = in + strlen(B) + 1; j < strlen(A) + 114; j++) {
    C[j] = A[j - strlen(B)];
  }
  return 0;
}
void Server_web() {
  server.on("/on",
            HTTP_GET,
            []
  {
    Insert(FR_init, FR_on, 626);
    server.setContentLength(sizeof(C));
    server.send(200, "text/html");
    server.sendContent(C, sizeof(C));
    digitalWrite(output, HIGH);
    Serial.println("LED ON");
  });
  server.on("/off",
            HTTP_GET,
            []
  {
    Insert(FR_init, FR_off, 626);
    server.setContentLength(sizeof(C));
    server.send(200, "text/html");
    server.sendContent(C, sizeof(C));
    digitalWrite(output, LOW);
    Serial.println("LED OFF");
  });
}
void setup()
{
  Serial.begin(115200); //开始串口通讯
  Serial.println();
  //管脚初始化：
  pinMode(output, OUTPUT);
  //设置初始值为低电平
  digitalWrite(output, LOW);
  /*准备网络*/
  WiFi.persistent(true); //网络持续模式关闭
  WiFi.mode(WIFI_STA);    //工作站模式
  //WiFi.disconnect();   //断开当前可能的连接
  delay(100);
  Serial.println("scan start");
  int n = WiFi.scanNetworks(); //扫描并返回搜索到的网络数量，该方法默认会阻塞
  Serial.println("scan done");
  if (n != 0)
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      Serial.println();
      Serial.print(i + 1);
      Serial.print(":       ");
      Serial.print(WiFi.SSID(i)); //打印网络名称
      Serial.print("        ");
      Serial.print(WiFi.RSSI(i)); //打印信号强度
      Serial.print("        ");
      Serial.print((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "未加密" : "加密"); //打印是否加密
      delay(10);
    }
  }
  WiFi.begin(QSSID, PASSw);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2500);
    Serial.println("连接中...");
    Serial.println(QSSID);
    WiFi.begin(QSSID, PASSw);

  }
  Serial.print("登录:http://");
  Serial.print(WiFi.localIP());
  Serial.print("/on");
  Server_web();
  server.begin();
}
void loop()
{
  server.handleClient();
}
