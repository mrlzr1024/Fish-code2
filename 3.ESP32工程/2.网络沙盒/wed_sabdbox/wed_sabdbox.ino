#include "esp_camera.h"
#include <WiFi.h>
#include <Arduino.h>
#define CAMERA_MODEL_AI_THINKER

const char *ssid = "热点";
const char *password = "密码";
WiFiServer server(800) //端口号
#if defined(CAMERA_MODEL_WROVER_KIT)
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 21
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#else
//#error "Camera model not selected"
#endif
    float cm;
void startCameraServer();
void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(4, OUTPUT);
  pinMode(2, INPUT);
  // pinMode(12, OUTPUT); pinMode(13, OUTPUT); pinMode(14, OUTPUT); pinMode(15, OUTPUT); // set the LED pin mode
  ledcSetup(9, 500, 8);  // 设置通道
                         // ledcAttachPin(12, 9);  // 将通道与对应的引脚连接
  ledcSetup(8, 10, 8);   // 设置通道
  ledcSetup(10, 500, 8); // 设置通道
                         // ledcAttachPin(14, 10);  // 将通道与对应的引脚连接
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //高规格的init可以预先分配更大的缓冲区
  if (psramFound())
  {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  }
  else
  {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  // drop down frame size for higher initial frame rate
  sensor_t *s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_SVGA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  startCameraServer();
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");
  server.begin();
}
int v1 = 0, v = 0;
char m1 = '0', m = '0';
void loop()
{
  WiFiClient client = server.available(); // listen for incoming clients用于接收信息
  if (client)
  {
    digitalWrite(2, LOW);
    client.print("Welcome back");
    // client.println();// if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then读去一个字符
        if (c == 'm')
        {                    // if the byte is a newline character查看是否是m
          c = client.read(); // read a byte, then
          if (c == '=')
          {
            m = client.read(); // 得到m的值用来控制方向
            Serial.write(m);   // print it out the serial monitor串口输出
          }
        }
        else if (c == 'v')
        {                    // if the byte is a newline character查看v就是占空比用来控制速度
          c = client.read(); // read a byte, then
          if (c == '=')
          {
            c = client.read();
            if ('0' <= c <= '9')
            {
              v = 0;
              v = 10 * v + c - '0';
            } //得到十位数
            c = client.read();
            if ('0' <= c <= '9')
              v = 10 * v + c - '0'; //个位
            c = client.read();
            if ('0' <= c <= '9')
              v = 10 * v + c - '0';
            c = client.read();
            ledcWrite(9, v / 2);
            ledcWrite(10, v); // read a byte, then用于获得拐弯时不同的速度，这里速度差一半
            Serial.write(c);  // print it out the serial monitor
          }
        }
        if (m1 != m || v1 != v)
        {
          m1 = m;
          v1 = v;
          switch (m - '0')
          {       // print it out the serial monitor
          case 0: // 8号通道占空比为零，就是停止然后就是输出端口和通道的绑定
            ledcAttachPin(12, 8);
            ledcAttachPin(14, 8);
            ledcAttachPin(13, 8);
            ledcAttachPin(15, 8);
            break;
          case 1:
            ledcAttachPin(12, 10);
            ledcAttachPin(14, 10);
            ledcAttachPin(13, 8);
            ledcAttachPin(15, 8);
            break;
          case 2:
            ledcAttachPin(13, 10);
            ledcAttachPin(15, 10);
            ledcAttachPin(12, 8);
            ledcAttachPin(14, 8);
            break;
          case 3:
            ledcAttachPin(13, 10);
            ledcAttachPin(14, 10);
            ledcAttachPin(12, 8);
            ledcAttachPin(15, 8);
            break;
          case 4:
            ledcAttachPin(12, 10);
            ledcAttachPin(15, 10);
            ledcAttachPin(13, 8);
            ledcAttachPin(14, 8);
            break;
          case 5:
            ledcAttachPin(12, 9);
            ledcAttachPin(14, 10);
            ledcAttachPin(13, 8);
            ledcAttachPin(15, 8);
            break;
          case 6:
            ledcAttachPin(12, 10);
            ledcAttachPin(14, 9);
            ledcAttachPin(13, 8);
            ledcAttachPin(15, 8);
            break;
          case 7:
            ledcAttachPin(13, 10);
            ledcAttachPin(15, 9);
            ledcAttachPin(12, 8);
            ledcAttachPin(14, 8);
            break;
          case 8:
            ledcAttachPin(13, 9);
            ledcAttachPin(15, 10);
            ledcAttachPin(12, 8);
            ledcAttachPin(14, 8);
            break;
          case 9:
            digitalWrite(4, HIGH);
            break;
          case 49:
            digitalWrite(4, LOW);
            break;                //可以写成‘a'懒得改了
          case 50:                //这段是超声波测距
            digitalWrite(4, LOW); //低高低电平发一个短时间脉冲去TrigPin
            delayMicroseconds(2);
            digitalWrite(4, HIGH);
            delayMicroseconds(10);
            digitalWrite(4, LOW);
            cm = pulseIn(2, HIGH) / 58.0;   //将回波时间换算成cm
            cm = (int(cm * 100.0)) / 100.0; //保留两位小数
            Serial.print(cm);
            Serial.print("cm");
            Serial.println();
            client.print(cm);
            client.print("cm");
            break;
          default:
            break;
          }
        }
      }
    }
    // close the connection:
    client.stop(); //通讯中断时停止
    ledcAttachPin(12, 8);
    ledcAttachPin(14, 8);
    ledcAttachPin(13, 8);
    ledcAttachPin(15, 8);
    digitalWrite(2, HIGH);
    Serial.println("Client Disconnected.");
  }
  // put your main code here, to run repeatedly:
  delay(10000);
}
