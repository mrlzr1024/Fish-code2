#include "key.h"
void setup()
{
  char i = 1;

  delay(3000);

  Serial2.begin(9600);                //波特率9600
  delay(10);                          //延时10ms
  JQ8x00_Command_Data(SetVolume, 15); //设置音量为30
  delay(10);                          //延时10ms

  if (JQ8X00_BusyCheck)
    pinMode(IO_JQ8X00_BusyCheck, INPUT_PULLUP); //忙检测引脚初始化

  Serial.begin(9600);
  //串口的开启，这里还可以传一些别的参数，但是我们只传入下面四个最重要的：波特率，默认SERIAL_8N1为8位数据位、无校验、1位停止位，后面两个分别为 14-RXD,15-TXD 引脚
  MySerial_stm32.begin(115200, SERIAL_8N1, 14, 15);

  key_init(); //按键中断初始化

  keyvalue_read(); //从内部空间中读取数据

  // RTC初始化
  Serial.println("Initialization DS307:");
  // Wire.begin(21, 23);//不写这一句就默认选择当前开发板类型的iic引脚，例如esp32的SDA-21、SCL-22，也可以任意改变iic引脚
  if (!rtc.begin())
  {
    Serial.println("DS307 初始化失败，请查看接线情况！");
    while (1)
      ;
  }
  else
    Serial.println("DS307 succeed！");

  // WiFi连接
  Serial.println("Initialization time:");
  Serial.print("Wifi connection");
  WiFi.begin(ssid, password);
  for (i = 1; i <= 50 && WiFi.status() != WL_CONNECTED; i++) // 5s内连接不成功就取消wifi自动校准时间，就直接用DS1307的时钟30
  {
    delay(250);
    Serial.print(".");
  }

  if (i <= 10) //若连接成功就开始校准网络时间
  {
    // 从网络时间服务器上获取并设置时间
    // 获取成功后esp芯片会使用RTC时钟保持时间的更新
    Serial.println("WiFi succeed!");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    adjust_time(); //重新设置DS1037时钟的时间
  }
  else
    Serial.println("WiFi not succeed!");

  // printLocalTime();

  WiFi.disconnect(true);
  //设置为true，那么就会关闭无线终端模式。
  //设置为false，则SSID和密码将会被设置为空值，同时还会使ESP32模块与接入点断开连接。但仍然处于无线终端模式，只是清除了SSID和密码
  WiFi.mode(WIFI_OFF); //这一句的功能感觉和上一句一样

  Serial.println("WiFi Mode:");
  Serial.println(WiFi.getMode()); // 告知用户设备当前工作模式
  Serial.println("WiFi disconnected!");

  SerialBT.begin("ESP32BT_T"); //蓝牙开始并设置名称

  MySerial_stm32.println("DIR(1);\r\n");
  delay(50);

    esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 1);//唤醒引脚，高电平唤醒
    Serial.printf("the wakeup reason is :%d\r\n", esp_sleep_get_wakeup_cause());

  ticker1.attach(0.08, callback1);                                      //每80毫秒后调用一次callback1
  ticker2.attach(0.5, callback2);                                       //每0.5秒调用callback2
  xTaskCreatePinnedToCore(core0code, "Task1", 10000, NULL, 0, NULL, 0); //在内核0上运行，loop和setup在内核1上运行
  display_main(1);                                                      //显示主状态
}


void loop()
{
  //Serial.println(xPortGetCoreID());
  xPortGetCoreID();
  if (call_num == 2 && loop_flag)
  {
    Serial.println("主循环运行中");
    loop_flag = 0;
  }
  else if (call_num != 2)
    loop_flag = 1;

  if(sha_flag)
  {
    display_main(1); //显示主状态(全刷新)
    sha_flag = 0;
  }
  else display_main(); //显示主状态
  key_pro();      //按键处理函数

  val = analogRead(34); //读取模拟量
  double temp;
  temp = (double)(val / 2048.0) * 330; //转化为温度((3.3 * 1000)/1024.0/10.0) = 0.322265625;
  // Serial.print("Temperature:");
  // Serial.println(temp);
  sprintf(buff, "SBC(15);DCV16(20,55,'%.2f C',1);\r\n", temp); //温度
  MySerial_stm32.println(buff);
  delay(50);
  // printLocalTime();//打印主控内部时间（注：若是未连接WIFI会执行很久）
}

