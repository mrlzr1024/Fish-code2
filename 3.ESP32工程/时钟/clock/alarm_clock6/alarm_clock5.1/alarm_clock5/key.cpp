#include "key.h"
//变量表=======================================================//
//变量表=======================================================//


Ticker ticker1; //声明Ticker对象
Ticker ticker2; //声明Ticker对象

HardwareSerial MySerial_stm32(1);


BluetoothSerial SerialBT; //定义蓝牙串口通讯名称
RTC_DS3231 rtc;
//网络相关
const char *ssid = "Chen";         //你的网络名称
const char *password = "12345678"; //你的网络密码
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600; //对于东八区（UTC/GMT+08:00）来说该参数就需要填写 8 * 3600
const int daylightOffset_sec = 0;    //如果使用夏令时 daylightOffset_sec 就填写3600，否则就填写0
char value_baoshi = 25;              //任意值
////显示相关///////////////////////////////////////////////////////////////////////////////////////
int val;
char buff[50]; // 显示屏模块缓存区
DateTime time_now;
char key_number = 0;  //按键标识
uchar bri_value = 10; // 10 - 最亮
bool sha_flag = 1;
////温度相关///////////////////////

Uion u;
////闹钟相关////////////////////////
char ala_xiang = 1; //哪个闹钟响
char alarm_clock;   //闹钟设置模式：当前处于哪个闹钟

unsigned long previousMillis = 0; //毫秒时间记录
const long   interval = 20000;      //时间间隔
unsigned long currentMillis;      //读取当前时间
char call_num = 0; //定时器中断函数2的计数个数
bool loop_flag = 1; //主循环的运行标志（每秒打印一次）
String rev;
String reslurt;
String inString;
int y;
//变量表=======================================================//
//变量表=======================================================//










/*奇奇怪怪的函数(蓝牙)*/
void blu_set_ala(String);
void adjest_N(String);
void blu_set_hour(String);
void blu_set_yee(String);
/*奇奇怪怪的函数(蓝牙)*/
////中断函数_start///////////////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR key_zd1() //中断函数
{
    // delay(10);   //消除抖动 一般大约10ms
    // if(key_1 == 1)    //再次判断按键是否按下
    //{
    key_number = 1;
    Serial.println("key_1");
    //}
}
void IRAM_ATTR key_zd2() //中断函数
{
    // delay(10);   //消除抖动 一般大约10ms
    // if(key_2 == 1)    //再次判断按键是否按下
    //{
    key_number = 2;
    Serial.println("key_2");
    //}
}
void IRAM_ATTR key_zd3() //中断函数
{
    // delay(10);   //消除抖动 一般大约10ms
    // if(key_3 == 1)    //再次判断按键是否按下
    //{
    key_number = 3;
    Serial.println("key_3");
    //}
}
void IRAM_ATTR key_zd4() //中断函数
{
    // delay(10);   //消除抖动 一般大约10ms
    // if(key_4 == 1)    //再次判断按键是否按下
    //{
    key_number = 4;
    Serial.println("key_4");
    //}
}
void IRAM_ATTR key_zd5() //中断函数
{
    // delay(10);   //消除抖动 一般大约10ms
    // if(key_5 == 1)    //再次判断按键是否按下
    //{
    key_number = 5;
    Serial.println("key_5");
    //}
}
////中断函数_end///////////////////////////////////////////////////////////////////////////////////////

////按键相关函数_start///////////////////////////////////////////////////////////////////////////////////////
void key_init()
{
    pinMode(key_1, INPUT_PULLUP);
    pinMode(key_2, INPUT_PULLUP);
    pinMode(key_3, INPUT_PULLUP);
    pinMode(key_4, INPUT_PULLUP);
    pinMode(key_5, INPUT_PULLUP);
    pinMode(key_6, INPUT);
}
void key_scan()
{
    if (digitalRead(key_1) == 0) //判断按键是否按下1代表已经按下
    {
        delay(50);
        if (digitalRead(key_1) == 0)
            key_number = 1;
        while (!digitalRead(key_1))
            ; //等待按键松开
    }

    if (digitalRead(key_2) == 0) //判断按键是否按下1代表已经按下
    {
        delay(50);
        if (digitalRead(key_2) == 0)
            key_number = 2;
        while (!digitalRead(key_2))
            ; //等待按键松开
    }

    if (digitalRead(key_3) == 0) //判断按键是否按下1代表已经按下
    {
        delay(50);
        if (digitalRead(key_3) == 0)
            key_number = 3;
        while (!digitalRead(key_3))
            ; //等待按键松开
    }

    if (digitalRead(key_4) == 0) //判断按键是否按下1代表已经按下
    {
        delay(50);
        if (digitalRead(key_4) == 0)
            key_number = 4;
        while (!digitalRead(key_4))
            ; //等待按键松开
    }

    if (digitalRead(key_5) == 0) //判断按键是否按下1代表已经按下
    {
        delay(50);
        if (digitalRead(key_5) == 0)
            key_number = 5;
        while (!digitalRead(key_5))
            ; //等待按键松开
    }

    if (digitalRead(key_6) == 1) //判断按键是否按下1代表已经按下
    {
        delay(50);
        if (digitalRead(key_6) == 1)
        {
            baoshi();
        }
        while (digitalRead(key_6))
            ; //等待按键松开
    }
}
////按键相关函数_end///////////////////////////////////////////////////////////////////////////////////////

////其他函数_start///////////////////////////////////////////////////////////////////////////////////////
char *change_int(int num, char str[])
{
    if (num >= 10)
        sprintf(str, "%d", num);
    else
        sprintf(str, "0%d", num);
    // Serial.printf(str);
    return str;
}
////其他函数_end///////////////////////////////////////////////////////////////////////////////////////

////初始化函数_start///////////////////////////////////////////////////////////////////////////////////////
void printLocalTime()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) //取得芯片本地时间，若是未连接wifi就会获取不到
    {
        Serial.println("Failed to obtain WiFi time");
        return;
    }
    Serial.println(&timeinfo, "%F %T %A"); // 格式化输出%A, %Y-%m-%d %H:%M:%S
}
void adjust_time()
{
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) //取得esp芯片本地时间-no，若是未连接wifi就会获取不到
    {
        Serial.println("Failed to obtain WiFi time!(Adjust_time)");
        return;
    }
    else //取得芯片本地时间-yes
    {
        //校准DS307时间为网络时间
        rtc.adjust(DateTime(timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec)); //年 月 日 时 分钟 秒
    }
}
void keyvalue_read() //从内部空间中读取数据
{
    char i = 0;
    char str[] = "alarm_clock*";
    for (i = 0; i <= 4; i++)
    {
        Preferences prefs; // 声明Preferences对象
        str[11] = '0' + i; //存储的空间内从0开始
        Serial.println(str);
        prefs.begin(str); // 打开命名空间alarm_clock1

        stru_alaclo[i].t_hour = prefs.getUChar("t_hour");     // defaultValue = 0         //时
        stru_alaclo[i].t_minute = prefs.getUChar("t_minute"); // defaultValue = 0     //分
        stru_alaclo[i].model = prefs.getUChar("model");       // defaultValue = 0           //模式
        // stru_alaclo[i].choo_day = prefs.getString("choo_day", "123456").c_str();            //选定星期闹铃下启用的日期
        strcpy(stru_alaclo[i].choo_day, prefs.getString("choo_day", "123456").c_str());
        stru_alaclo[i].ala_flag = prefs.getBool("ala_flag"); // defaultValue = false  //是否启用

        Serial.println(stru_alaclo[i].choo_day);
        if (stru_alaclo[i].choo_day[7] == '\0')
            Serial.printf("Yes");
        Serial.printf("当前闹钟：%d\n时间：%d:%d\n模式：%d\n启用日期：%c-%c-%c %c-%c-%c-%c\n启用：%d\n\n", i + 1, stru_alaclo[i].t_hour, stru_alaclo[i].t_minute, stru_alaclo[i].model, stru_alaclo[i].choo_day[0], stru_alaclo[i].choo_day[1], stru_alaclo[i].choo_day[2], stru_alaclo[i].choo_day[3], stru_alaclo[i].choo_day[4], stru_alaclo[i].choo_day[5], stru_alaclo[i].choo_day[6], stru_alaclo[i].ala_flag);
        prefs.end(); // 关闭当前命名空间
    }
}
void keyvalue_write()
{
}
////初始化函数_end///////////////////////////////////////////////////////////////////////////////////////

////显示函数_start///////////////////////////////////////////////////////////////////////////////////////
void display_main(bool flag) //主界面仅显示
{
    static char old_value = 69;
    char str1[10], str2[10];
    time_now = rtc.now();
    if (flag)
    {
        sprintf(buff, "CLR(0);\r\n"); //清屏
        MySerial_stm32.print(buff);
        delay(50);

        if (stru_alaclo[0].ala_flag == 1) //闹钟1启用
        {
            sprintf(buff, "SBC(0);DCV16(0,80,'%s:%s',16);\r\n", change_int(stru_alaclo[0].t_hour, str1), change_int(stru_alaclo[0].t_minute, str2)); //主界面闹钟1位置
            MySerial_stm32.print(buff);
            delay(50);
        }
        if (stru_alaclo[1].ala_flag == 1) //闹钟2启用
        {
            sprintf(buff, "SBC(0);DCV16(0,96,'%s:%s',16);\r\n", change_int(stru_alaclo[1].t_hour, str1), change_int(stru_alaclo[1].t_minute, str2)); //闹钟2位置
            MySerial_stm32.print(buff);
            delay(50);
        }
        if (stru_alaclo[2].ala_flag == 1) //闹钟3启用
        {
            sprintf(buff, "SBC(0);DCV16(0,112,'%s:%s',16);\r\n", change_int(stru_alaclo[2].t_hour, str1), change_int(stru_alaclo[2].t_minute, str2)); //闹钟3位置
            MySerial_stm32.print(buff);
            delay(50);
        }
        if (stru_alaclo[3].ala_flag == 1) //闹钟4启用
        {
            sprintf(buff, "SBC(0);DCV16(60,80,'%s:%s',16);\r\n", change_int(stru_alaclo[3].t_hour, str1), change_int(stru_alaclo[3].t_minute, str2)); //闹钟4位置
            MySerial_stm32.print(buff);
            delay(50);
        }
        if (stru_alaclo[4].ala_flag == 1) //闹钟5启用
        {
            sprintf(buff, "SBC(0);DCV16(60,96,'%s:%s',16);\r\n", change_int(stru_alaclo[4].t_hour, str1), change_int(stru_alaclo[4].t_minute, str2)); //闹钟5位置
            MySerial_stm32.print(buff);
            delay(50);
        }
    }

    if (old_value != time_now.minute() || flag)
    {
        sprintf(buff, "SBC(15);DCV24(80,35,'%s:%s',1);\r\n", change_int(time_now.hour(), str1), change_int(time_now.minute(), str2)); //时分显示
        MySerial_stm32.println(buff);
        delay(50);

        sprintf(buff, "DCV16(0,30,'%s',1);\r\n", daysOfTheWeek[time_now.dayOfTheWeek()]);
        MySerial_stm32.println(buff); //星期
        delay(50);

        sprintf(buff, "SBC(15);DCV24(20,0,'%d-%s-%s',1);\r\n", time_now.year(), change_int(time_now.month(), str1), change_int(time_now.day(), str2)); //年月日time_now.month()
        MySerial_stm32.println(buff);
        delay(50);

        // Serial.printf("%d-%d-%d\n", time_now.year(), time_now.month(), time_now.day());
        old_value = time_now.minute();
    }
}
void display_alaclo(bool flag ) //闹钟界面仅显示
{
    // str_model
    char str1[10], str2[10];
    if (flag)
    {
        sprintf(buff, "CLR(0);\r\n"); //清屏
        MySerial_stm32.print(buff);
        delay(50);

        MySerial_stm32.print("SBC(15);DC16(20,80,'Pattern:',1);\r\n"); // 显示模式字符串标识
        delay(50);
    }

    if (stru_alaclo[alarm_clock].ala_flag == 1)
    {
        MySerial_stm32.printf("CIR(90,15,12,1);\r\n");
        delay(50);
    }
    else
    {
        MySerial_stm32.printf("CIR(90,15,12,0);\r\n");
        delay(50);
    }

    sprintf(buff, "SBC(15);DCV16(10,10,'%s %d',1);\r\n", "Colock", alarm_clock + 1);
    Serial.print("Colock=");
    Serial.println(alarm_clock + 1);
    MySerial_stm32.print(buff);
    delay(50);

    sprintf(buff, "SBC(15);DCV32(35,35,'%s:%s',1);\r\n", change_int(stru_alaclo[alarm_clock].t_hour, str1), change_int(stru_alaclo[alarm_clock].t_minute, str2)); //闹钟时间位置
    MySerial_stm32.print(buff);
    delay(50);

    sprintf(buff, "SBC(15);DCV24(20,96,'%s',1);\r\n", str_model[stru_alaclo[alarm_clock].model]); //显示当前闹钟的模式
    MySerial_stm32.print(buff);
    delay(50);
}
//响铃界面显示
////显示函数_end///////////////////////////////////////////////////////////////////////////////////////

////设置函数_start///////////////////////////////////////////////////////////////////////////////////////
void display_set() //主界面-年 月 日 时 分钟设置
{
    key_number = 0;
    time_now = rtc.now();
    char change_flag = 0; //修改的标志
    char i = 0;
    char str[10];
    char blank[5][5] = {"    ", "  ", "  ", "  ", "  "}; //空白符
    char none_str[5][10];
    int str_num[5] = {time_now.year(), time_now.month(), time_now.day(), time_now.hour(), time_now.minute()};
    uchar str_x[5][2] = {{20, 0}, {80, 0}, {115, 0}, {80, 35}, {115, 35}}; // 时间坐标值

    previousMillis = millis(); //读取当前时间
    while (1)
    {
        currentMillis = millis();                       //读取当前时间
        if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
            break;

        throb_time(24, str_x[i][0], str_x[i][1], blank[i], change_int(str_num[i], str)); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
        if (key_number == 1)                                                             //设置设置完成键
        {
            //校准DS307时间为设定时间
            if (change_flag == 1)
            {
                value_baoshi = 25;                                                                   //报时值，任意值
                rtc.adjust(DateTime(str_num[0], str_num[1], str_num[2], str_num[3], str_num[4], 0)); //年 月 日 时 分钟 秒
            }
            display_main(1);           //重新显示时间
            previousMillis = millis(); //读取当前时间
            break;
        }
        else if (key_number == 3) //时间递增
        {
            change_flag = 1;
            if (i == 1) //当前设置月份
            {
                str_num[1]++;
                if (str_num[1] > 12)
                    str_num[1] = 1;
                if (str_num[1] == 2 && str_num[2] > 28) //当设置月份时，检查日期是否对应月份,不对应
                {
                    str_num[2] = 28;
                    throb_time(24, str_x[2][0], str_x[2][1], blank[2], change_int(str_num[2], str)); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
                }
                if (str_num[2] > 30 && (str_num[1] == 4 || str_num[1] == 6 || str_num[1] == 9 || str_num[1] == 11))
                {
                    str_num[2] = 30;
                    throb_time(24, str_x[2][0], str_x[2][1], blank[2], change_int(str_num[2], str)); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
                }
            }
            else if (i == 2) //当前设置日份
            {
                str_num[2]++;
                if ((str_num[2] > 28 && str_num[1] == 2) ||
                    (str_num[2] > 30 && (str_num[1] == 4 || str_num[1] == 6 || str_num[1] == 9 || str_num[1] == 11)) ||
                    (str_num[2] > 31 && (str_num[1] == 1 || str_num[1] == 3 || str_num[1] == 5 || str_num[1] == 7 || str_num[1] == 8 || str_num[1] == 10 || str_num[1] == 12)))
                    str_num[2] = 1;
            }
            else if (i == 3) //当前设置小时
            {
                str_num[3]++;
                if (str_num[3] > 23)
                    str_num[3] = 0;
            }
            else if (i == 4) //当前设置分钟
            {
                str_num[4]++;
                if (str_num[4] > 59)
                    str_num[4] = 0;
            }
            else
                str_num[0]++; //当前设置年份
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 2) //时间递减
        {
            change_flag = 1;
            if (i == 1) //当前设置月份
            {
                str_num[1]--;
                if (str_num[1] < 1)
                    str_num[1] = 12;
                if (str_num[1] == 2 && str_num[2] > 28) //当设置月份时，检查日期是否对应月份,不对应
                {
                    str_num[2] = 28;
                    throb_time(24, str_x[2][0], str_x[2][1], blank[2], change_int(str_num[2], str)); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
                }
                if (str_num[2] > 30 && (str_num[1] == 4 || str_num[1] == 6 || str_num[1] == 9 || str_num[1] == 11))
                {
                    str_num[2] = 30;
                    throb_time(24, str_x[2][0], str_x[2][1], blank[2], change_int(str_num[2], str)); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
                }
            }
            else if (i == 2) //当前设置日份
            {
                str_num[2]--;
                if (str_num[2] < 1)
                {
                    if (str_num[1] == 2)
                        str_num[2] = 28;
                    if (str_num[1] == 4 || str_num[1] == 6 || str_num[1] == 9 || str_num[1] == 11)
                        str_num[2] = 30;
                    if (str_num[1] == 1 || str_num[1] == 3 || str_num[1] == 5 || str_num[1] == 7 || str_num[1] == 8 || str_num[1] == 10 || str_num[1] == 12)
                        str_num[2] = 31;
                }
            }
            else if (i == 3) //当前设置小时
            {
                str_num[3]--;
                if (str_num[3] < 0)
                    str_num[3] = 23;
            }
            else if (i == 4) //当前设置分钟
            {
                str_num[4]--;
                if (str_num[4] < 0)
                    str_num[4] = 59;
            }
            else
                str_num[0]--; //当前设置年份
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 4) //设置下一个时间变量
        {
            i++;
            if (i > 4)
                i = 0;
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
    }
}
void display_set_ala() //闹钟界面-时/分设置
{
    char blank[] = "  ";                      //空白符
    uchar str_x[2][2] = {{35, 35}, {81, 35}}; // 时间坐标值
    char i = 0;                               //循环次数
    char str[10];                             //缓冲区
    int str_num[2] = {stru_alaclo[alarm_clock].t_hour, stru_alaclo[alarm_clock].t_minute};

    previousMillis = millis(); //读取当前时间
    while (1)
    {
        currentMillis = millis();                       //读取当前时间
        if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
            break;

        throb_time(32, str_x[i][0], str_x[i][1], blank, change_int(str_num[i], str)); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
        if (key_number == 1)                                                          //设置完成键
        {
            stru_alaclo[alarm_clock].t_hour = str_num[0];
            stru_alaclo[alarm_clock].t_minute = str_num[1];
            previousMillis = millis(); //读取当前时间
            break;
        }
        else if (key_number == 2) //时间递减
        {
            str_num[i]--;
            if (i == 0 && str_num[0] < 0) //当前设置小时
                str_num[0] = 23;
            if (i == 1 && str_num[1] < 0) //当前设置分钟
                str_num[1] = 59;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 3) //时间递增
        {
            str_num[i]++;
            if (i == 0 && str_num[0] > 23) //当前设置小时
                str_num[0] = 0;
            if (i == 1 && str_num[1] > 59) //当前设置分钟
                str_num[1] = 0;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 4) //下一个时间值
        {
            ++i;
            if (i > 1)
                i = 0;
            previousMillis = millis(); //读取当前时间
        }
        key_number = 0;
    }
}
void display_set_model() //闹钟界面-模式设置
{
    char blank[] = "          ";              //空白符
    uchar str_x[2] = {20, 96};                // 时间坐标值
    uchar i = stru_alaclo[alarm_clock].model; //当前的模式
    char str[10];                             //缓冲区

    previousMillis = millis(); //读取当前时间
    while (1)
    {
        currentMillis = millis();                       //读取当前时间
        if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
            break;

        throb_time(24, str_x[0], str_x[1], blank, str_model[i]); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
        if (key_number == 1)                                     //设置完成键
        {
            stru_alaclo[alarm_clock].model = i;
            previousMillis = millis(); //读取当前时间
            break;
        }
        else if (key_number == 2) //模式递减
        {
            i--;
            if (i < 0)
                i = 0;
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 3) //模式递增
        {
            i++;
            if (i > 3) //选定模式
            {
                i = 3;
                key_number = 0;
                display_set_choose(); //闹钟界面-自定义闹钟选定日期
            }

            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
    }
}
void display_set_choose() //闹钟界面-自定义闹钟选定日期
{
    char blank[] = " "; //空白符
    char str_kc[] = "1";
    uchar str_x[7][2] = {{6, 0}, {30, 0}, {54, 0}, {78, 0}, {102, 0}, {6, 30}, {30, 30}};         // 数字坐标值
    uchar xy_cir[7][2] = {{12, 12}, {36, 12}, {60, 12}, {84, 12}, {108, 12}, {12, 42}, {36, 42}}; //圈的坐标
    uchar i = 0;                                                                                  //循环次数
    char str[10];                                                                                 //缓冲区
    char flag[7] = {stru_alaclo[alarm_clock].choo_day[0], stru_alaclo[alarm_clock].choo_day[1], stru_alaclo[alarm_clock].choo_day[2], stru_alaclo[alarm_clock].choo_day[3],
                    stru_alaclo[alarm_clock].choo_day[4], stru_alaclo[alarm_clock].choo_day[5], stru_alaclo[alarm_clock].choo_day[6]};

    sprintf(buff, "CLR(0);\r\n"); //屏幕清屏
    MySerial_stm32.print(buff);
    delay(50);
    throb_time(24, 20, 96, (char *)"         ", (char *)str_model[3]); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
    MySerial_stm32.print("SBC(15);DCV24(6,0,'1',1);\r\n");             //选定模式的数字
    delay(50);
    MySerial_stm32.print("SBC(15);DCV24(30,0,'2',1);\r\n");
    delay(50);
    MySerial_stm32.print("SBC(15);DCV24(54,0,'3',1);\r\n");
    delay(50);
    MySerial_stm32.print("SBC(15);DCV24(78,0,'4',1);\r\n");
    delay(50);
    MySerial_stm32.print("SBC(15);DCV24(102,0,'5',1);\r\n");
    delay(50);
    MySerial_stm32.print("SBC(15);DCV24(6,30,'6',1);\r\n");
    delay(50);
    MySerial_stm32.print("SBC(15);DCV24(30,30,'7',1);\r\n");
    delay(50);
    for (i = 0; i <= 6; i++) //是否选定当前日期（画圈）
    {
        if (flag[i] == '1')
        {
            sprintf(buff, "CIR(%d,%d,12,1);\r\n", xy_cir[i][0], xy_cir[i][1]);
            MySerial_stm32.printf(buff);
            delay(50);
        }
    }
    i = 0;

    previousMillis = millis(); //读取当前时间
    while (1)
    {
        currentMillis = millis();                       //读取当前时间
        if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
            break;

        str_kc[0] = '1' + i;
        throb_time(24, str_x[i][0], str_x[i][1], blank, str_kc); //闪烁函数，字体大小，x_坐标，y_坐标，空白字符串，有效字符串
        if (key_number == 1)                                     //设置完成键
        {
            char j;
            for (j = 0; j <= 6; j++)
            {
                // if(flag[j] == 1)
                //   Serial.printf("当前保存的闹钟：%d选定日期：%d\n", alarm_clock+1, j+1);
                stru_alaclo[alarm_clock].choo_day[j] = flag[j];
            }
            char k;
            for (k = 0; k <= 6; k++)
                Serial.printf("当前的闹钟：%d；（code变量）自定义的日期布尔值%d\n", alarm_clock + 1, stru_alaclo[alarm_clock].choo_day[k]);
            previousMillis = millis(); //读取当前时间
            break;
        }
        else if (key_number == 2) //数字递减
        {
            i--;
            if (i < 0)
                i = 0;
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 3) //数字递增
        {
            i++;
            if (i > 6)
                i = 6;
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
        else if (key_number == 4) //数字圈定键
        {
            if (flag[i] == '1')
            {
                flag[i] = '0';
                sprintf(buff, "CIR(%d,%d,12,0);\r\n", xy_cir[i][0], xy_cir[i][1]);
                MySerial_stm32.printf(buff);
                delay(50);
            }
            else if (flag[i] == '0')
            {
                flag[i] = '1';
                sprintf(buff, "CIR(%d,%d,12,1);\r\n", xy_cir[i][0], xy_cir[i][1]);
                MySerial_stm32.printf(buff);
                delay(50);
            }
            key_number = 0;
            previousMillis = millis(); //读取当前时间
        }
    }
    display_alaclo(1); //显示闹钟设置模式界面
}
////设置函数_end///////////////////////////////////////////////////////////////////////////////////////

////其他函数_start///////////////////////////////////////////////////////////////////////////////////////
void throb_time(uchar zt_size, uchar x, uchar y, char str_none[], char str_display[]) //目标位置闪烁函数
{
    char i = 0;
    sprintf(buff, "SBC(15);DCV%d(%d,%d,'%s',1);\r\n", zt_size, x, y, str_none); //空白显示
    MySerial_stm32.print(buff);
    for (i = 1; i <= 10; i++)
    {
        delay(20);
    }

    sprintf(buff, "SBC(15);DCV%d(%d,%d,'%s',1);\r\n", zt_size, x, y, str_display); //有效显示
    MySerial_stm32.print(buff);
    for (i = 1; i <= 15; i++)
    {
        delay(20);
    }
}
void baoshi() //报时函数
{
    time_now = rtc.now();
    Serial.println("语音报时");
    if (time_now.minute() == 0 && (time_now.hour() != (value_baoshi)))
    {
        zd_baoshi(time_now.hour()); //整点报时
    }
    else
    {
        Serial2.print("A");
        Serial2.print(time_now.hour());
        Serial2.print(":");
        Serial2.print(time_now.minute());
        Serial2.print("A");
    }
}
void zd_baoshi(uchar num) //整点报时函数
{
    uchar baoshi_zd[5] = {17}; //当前时间
    char i = 1;
    if (num == 0)
    {
        baoshi_zd[1] = 10; // 0
        baoshi_zd[2] = 18; //点整
        i = 3;
    }
    else if (num < 10)
    {
        baoshi_zd[1] = num;
        baoshi_zd[2] = 18; //点整
        i = 3;
    }
    else if (num == 10)
    {
        baoshi_zd[1] = 13; // 10
        baoshi_zd[2] = 18; //点整
        i = 3;
    }
    else if (num < 20 && num > 10)
    {
        baoshi_zd[1] = 13; // 10
        baoshi_zd[2] = num % 10;
        baoshi_zd[3] = 18; //点整
        i = 4;
    }
    else
    {
        baoshi_zd[1] = 2;  // 2
        baoshi_zd[2] = 13; // 10
        baoshi_zd[3] = num % 20;
        baoshi_zd[4] = 18; //点整
        i = 5;
    }
    JQ8x00_ZuHeBoFang(baoshi_zd, i);
}
// var
void pro_ala() //闹钟响铃处理函数
{
    char i;
    char k = time_now.dayOfTheWeek() - 1;
    if (k == -1)
        k = 6;

    for (i = 0; i <= 4; i++)
    {
        if ((stru_alaclo[i].ala_flag == 1) &&
            ((stru_alaclo[i].model == 0) ||                                                            //每天闹铃
             (stru_alaclo[i].model == 1 && k <= 4) ||                                                  //工作日闹铃(k<=4代表当前的星期是工作日)
             (stru_alaclo[i].model == 2) ||                                                            //单次闹铃
             (stru_alaclo[i].model == 3 && stru_alaclo[i].choo_day[k] == 1)) &&                        //自定义闹铃
            (stru_alaclo[i].t_hour == time_now.hour() && stru_alaclo[i].t_minute == time_now.minute()) //时间是否到达
        )
        {
            ala_xiang = i;
            if (stru_alaclo[i].ala_during == 1)
                break; //当前闹钟在时间到达时是已经响铃（continue）

            stru_alaclo[i].ala_during = 1; //响铃
            if (stru_alaclo[i].model == 2) //单次闹铃
                stru_alaclo[i].ala_flag = 0;
            Serial.printf("闹钟%d 响了\n", i + 1);
            Serial2.print("B");
        }
        else
        {
            stru_alaclo[i].ala_during = 0; //时间未到达,设置于为响铃状态
        }
    }
}
void key_pro() //主界面的按键处理函数
{
    if (key_number == 1) ////按键1 - 闹钟设置键
    {
        loop_alaclo();   //闹钟设置模式的循环函数
        display_main(1); //清屏并显示主状态
        key_number = 0;
    }
    else if (key_number == 2) //按键2 - 亮度调节
    {
        if (bri_value == 10)
        {
            bri_value = 100; //中等亮度
            Serial.println("当前亮度：中等亮度");
        }
        else if (bri_value == 100)
        {
            bri_value = 200; //最暗
            Serial.println("当前亮度：最暗亮度");
        }
        else
        {
            bri_value = 10; //最亮
            Serial.println("当前亮度：最亮亮度");
        }

        sprintf(buff, "BL(%2d);\r\n", bri_value);
        MySerial_stm32.println(buff); //发送显示数据
        delay(25);
        key_number = 0;
    }
    else if (key_number == 3) //按键3 - 贪睡（响铃状态生效）
    {
        if (ala_xiang != 10)
        {
            DateTime time_other;
            key_number = 0;
            Serial2.print("C");
            time_other = rtc.now();
            stru_alaclo[ala_xiang].ala_flag = true;
            stru_alaclo[ala_xiang].t_hour = time_other.hour();
            stru_alaclo[ala_xiang].t_minute = time_other.minute() + 5;
            char str[] = "alarm_clock*";
            str[11] = '0' + ala_xiang;                           //存储的空间内从0开始
            Preferences prefs;                                   // 声明Preferences对象
            prefs.begin(str);                                    // 打开命名空间alarm_clock*
            prefs.putUChar("t_hour", time_other.hour());         //时
            prefs.putUChar("t_minute", time_other.minute() + 5); //+5分
            prefs.putBool("ala_flag", true);                     //是否启用
            prefs.end();
            sha_flag = 1;
        }
    }
    else if (key_number == 4) //按键4 - 时间设置键
    {
        display_set(); //时间设置的界面
        key_number = 0;
    }
    else if (key_number == 5) //按键5 - wifi自动校准（休眠）
    {
        sprintf(buff, "CLR(0);\r\n"); //屏幕清屏
        MySerial_stm32.print(buff);
        delay(5);
        sprintf(buff, "BL(%2d);\r\n", bri_value);
        MySerial_stm32.println(buff); //发送显示数据
        delay(25);
        Serial.println("ESP32 will sleep now!");
        esp_deep_sleep_start(); // esp_deep_sleep_start
                                //进入休眠

        key_number = 0;
    }
    else if (key_number == 6) //按键6 - 时间播报
    {
        Serial.println("播报");
        key_number = 0;
    }
}
void loop_alaclo() //闹钟设置界面的循环处理函数
{
    key_number = 0;
    alarm_clock = 0;   //当前处于闹钟1
    display_alaclo(1); //显示闹钟设置界面
    Serial.printf("当前闹钟%d：\n", alarm_clock + 1);

    previousMillis = millis();
    while (1)
    {
        display_alaclo(); //显示闹钟设置界面

        currentMillis = millis();                       //读取当前时间
        if (currentMillis - previousMillis >= interval) //如果和前次时间大于等于时间间隔
            break;

        if (key_number == 1) //按键1 - 闹钟启用确定/取消键
        {
            stru_alaclo[alarm_clock].ala_flag = !stru_alaclo[alarm_clock].ala_flag; //取反
            if (stru_alaclo[alarm_clock].ala_flag == 1)
            {
                Serial.printf("闹钟%d：启用\n", alarm_clock + 1);
            }
            else
                Serial.printf("闹钟%d：禁用\n", alarm_clock + 1);
            key_number = 0;
            previousMillis = millis();
        }
        else if (key_number == 2) //按键2 - 上一个闹钟
        {
            //存储设置值
            char str[] = "alarm_clock*";
            str[11] = '0' + alarm_clock;                                    //存储的空间内从0开始
            Preferences prefs;                                              // 声明Preferences对象
            prefs.begin(str);                                               // 打开命名空间alarm_clock*
            prefs.putUChar("t_hour", stru_alaclo[alarm_clock].t_hour);      //时
            prefs.putUChar("t_minute", stru_alaclo[alarm_clock].t_minute);  //分
            prefs.putUChar("model", stru_alaclo[alarm_clock].model);        //模式
            prefs.putString("choo_day", stru_alaclo[alarm_clock].choo_day); //选定星期闹铃下启用的日期
            prefs.putBool("ala_flag", stru_alaclo[alarm_clock].ala_flag);   //是否启用
            prefs.end();                                                    // 关闭当前命名空间

            if (alarm_clock != 0)
                alarm_clock--;
            Serial.printf("当前闹钟%d：\n", alarm_clock + 1);

            key_number = 0;
            previousMillis = millis();
        }
        else if (key_number == 3) //按键3 - 下一个闹钟
        {
            //存储设置值
            char str[] = "alarm_clock*";
            str[11] = '0' + alarm_clock;                                   //存储的空间内从0开始
            Preferences prefs;                                             // 声明Preferences对象
            prefs.begin(str);                                              // 打开命名空间alarm_clock*
            prefs.putUChar("t_hour", stru_alaclo[alarm_clock].t_hour);     //时
            prefs.putUChar("t_minute", stru_alaclo[alarm_clock].t_minute); //分
            char k;
            for (k = 0; k <= 6; k++)
                Serial.printf("当前的闹钟：%d；（code变量）设置的日期布尔值：%c\n", alarm_clock + 1, stru_alaclo[alarm_clock].choo_day[k]);
            prefs.putUChar("model", stru_alaclo[alarm_clock].model);                //模式
            prefs.putString("choo_day", String(stru_alaclo[alarm_clock].choo_day)); //选定星期闹铃下启用的日期
            prefs.putBool("ala_flag", stru_alaclo[alarm_clock].ala_flag);           //是否启用
            prefs.end();                                                            // 关闭当前命名空间

            prefs.begin(str); // 打开命名空间alarm_clock*
            char bb[10];
            strcpy(bb, stru_alaclo[alarm_clock].choo_day);
            strcpy(stru_alaclo[alarm_clock].choo_day, "4444444");
            Serial.println(stru_alaclo[alarm_clock].choo_day);
            strcpy(stru_alaclo[alarm_clock].choo_day, prefs.getString("choo_day", "66666").c_str());
            for (k = 0; k <= 6; k++)
                Serial.printf("当前提取的闹钟：%d；内部空间的布尔值：%c\n", alarm_clock + 1, stru_alaclo[alarm_clock].choo_day[k]);
            prefs.end(); // 关闭当前命名空间
            strcpy(stru_alaclo[alarm_clock].choo_day, bb);

            alarm_clock++;
            if (alarm_clock <= 4)
            {
                Serial.printf("当前闹钟%d：\n", alarm_clock + 1);
            }

            key_number = 0;
            previousMillis = millis();
        }
        else if (key_number == 4) //按键4 - 设置时间值
        {
            key_number = 0;
            display_set_ala(); //设置闹钟时间
            key_number = 0;
        }
        else if (key_number == 5) //按键5 - 模式选择
        {
            display_set_model(); //模式选择设置显示
            key_number = 0;
        }

        if (alarm_clock > 4)
            break;
    }
}
////按键扫描函数_end///////////////////////////////////////////////////////////////////////////////////////

////回调函数///////////////////////////////////////////////////////////////////////////////////////
void callback1() //回调函数
{
    key_scan();
    delay(1);  //延时1微妙（避免无限重启）
    pro_ala(); //闹钟响铃处理函数
               // vTaskDelay(1);
}

void callback2()
{
    call_num++;
    if (call_num >= 4)
    {
        call_num = 0;
    }
    delay(1); //延时1微妙（避免无限重启）
              // vTaskDelay(1);
}


////线程函数///////////////////////////////////////////////////////////////////////////////////////
void core0code(void *parameter)
{
    /**
       @brief
       小闹钟部分：
       1.只响一次：1 A 0000000 14:32
       2.每天：2 B 0000000 14:32
       3.工作日：3 C 0000000 14:32
       4.自定义：4 D 1101000 14:32
    */
    for (;;)
    {
        if (SerialBT.available())
        {                                //判断是否蓝牙有数据
            rev = SerialBT.readString(); //读蓝牙的数据
            Serial.println("数据来了");
            Serial.println("============================================");
            Serial.println(rev);
            if (rev != "X")
            {
                SerialBT.print(rev);
                Serial.printf("发送验证位： %s\n", rev);
                while (!SerialBT.available())
                    ;
                reslurt = SerialBT.readString(); //读蓝牙的数据
                Serial.println("数据是：");
                Serial.println(reslurt);
                SerialBT.print(rev);
                Serial.println("============================================");
            }
            else if (rev == "X")
            {
                Serial.println("检测到有传输失败现象");
                Serial.println("============================================");
                rev = " ";
            }
            /*======================================*/
            if (rev == "N")
            {
                adjest_N(reslurt);
                sha_flag = 1;
            }
            else if (rev == "H")
            {
                blu_set_hour(reslurt);
                sha_flag = 1;
            }
            else if (rev == "Y")
            {
                blu_set_yee(reslurt);
                sha_flag = 1;
            }
            /*======================================*/
            delay(1000);
        }
        delay(1); //延时1微妙（避免无限重启）
                  // vTaskDelay(1);
    }
}
void adjest_N(String word)
{
    /**
       @brief
       小闹钟部分：
       1.只响一次：1 A 0000000 14:32
       2.每天：2 B 0000000 14:32
       3.工作日：3 C 0000000 14:32
       4.自定义：4 D 1101000 14:32
    */
    /*0:1
      1:
      2:A
      3:
      4:0
      5:0
      6:0
      7:0
      8:0
      9:0
      10:0
      11:
      12:1
      13:4
      14::
      15:3
      16:2*/

    //存储设置值

    alarm_clock = int(word[0] - 49); //第几位闹钟(alarm_clock)
    Serial.print("alarm_clock:");
    Serial.println(alarm_clock);
    blu_set_ala(word);
    stru_alaclo[alarm_clock].ala_flag = true;
    char str[] = "alarm_clock*";
    str[11] = '0' + alarm_clock;                               //存储的空间内从0开始
    Preferences prefs;                                         // 声明Preferences对象
    prefs.begin(str);                                          // 打开命名空间alarm_clock*
    prefs.putUChar("t_hour", stru_alaclo[alarm_clock].t_hour); //时
    Serial.print(".t_hour=");
    Serial.println(int(stru_alaclo[alarm_clock].t_hour));
    prefs.putUChar("t_minute", stru_alaclo[alarm_clock].t_minute); //分
    Serial.print(".t_minute=");
    Serial.println(int(stru_alaclo[alarm_clock].t_minute));
    prefs.putUChar("model", stru_alaclo[alarm_clock].model); //模式
    Serial.print(".model=");
    Serial.println(int(stru_alaclo[alarm_clock].model));
    prefs.putString("choo_day", String(stru_alaclo[alarm_clock].choo_day)); //选定星期闹铃下启用的日期
    Serial.print(".choo_day=");
    Serial.println(stru_alaclo[alarm_clock].choo_day);
    prefs.putBool("ala_flag", stru_alaclo[alarm_clock].ala_flag); //是否启用
    prefs.end();
}
void blu_set_ala(String word) //闹钟界面设置
{
    uchar str_x[2][2] = {{35, 35}, {81, 35}}; // 时间坐标值
    char i = 0;                               //循环次数
    char str[10];                             //缓冲区
    int str_num[2] = {int((word[12] - 48) * 10 + word[13] - 48), int((word[15] - 48) * 10 + word[16] - 48)};
    Serial.print("t_hour:");
    Serial.println(str_num[0]);
    Serial.print("t_minute:");
    Serial.println(str_num[1]);
    /*=闹钟设置==*/
    stru_alaclo[alarm_clock].t_hour = str_num[0];
    stru_alaclo[alarm_clock].t_minute = str_num[1]; //设置完成
    /*=模式设置==*/
    switch (word[2])
    {
    case 'A':
        stru_alaclo[alarm_clock].model = 2;
        break;
    case 'B':
        stru_alaclo[alarm_clock].model = 0;
        break;
    case 'C':
        stru_alaclo[alarm_clock].model = 1;
        break;
    case 'D':
        stru_alaclo[alarm_clock].model = 3;
        break;
    }
    // stru_alaclo[alarm_clock].model = word[2] - 65; //当前的模式                          //缓冲区
    /*=周末设置==*/
    //循环次数                                                                               //缓冲区
    char flag[7] = {word[4], word[5], word[6], word[7],
                    word[8], word[9], word[10]};
    for (char j = 0; j <= 6; j++)
    {
        stru_alaclo[alarm_clock].choo_day[j] = flag[j];
    }
}
void blu_set_hour(String word) //主界面-时 分钟设置
{
    /*
      0:  1
      1:  4
      2:  :
      3:  3
      4:  1
    */
    DateTime time_other;
    Serial.println("进入");
    time_other = rtc.now();

    int str_num[5] = {time_other.year(),
                      time_other.month(),
                      time_other.day(),
                      (word[0] - 48) * 10 + word[1] - 48,
                      (word[3] - 48) * 10 + word[4] - 48};
    value_baoshi = 25;                                                                   //报时值，任意值
    rtc.adjust(DateTime(str_num[0], str_num[1], str_num[2], str_num[3], str_num[4], 0)); //年 月 日 时 分钟 秒

    Serial.println((word[0] - 48) * 10 + word[1] - 48);
    Serial.println((word[3] - 48) * 10 + word[4] - 48);
    time_other = rtc.now(); //读取当前时间
    Serial.println(time_other.hour());
    Serial.println(time_other.minute());
}
void blu_set_yee(String word) //主界面-时 分钟设置
{
    /*
        0:  2
        1:  0
        2:  2
        3:  2
        4:  - -   ----4
        5:  6 1
        6:  - 2
        7:  3 -
        8:  n 1
        9:  n 9
    */
    Serial.println(word);
    DateTime time_now2022;
    time_now2022 = rtc.now();
    char change_flag = 0; //修改的标志
    String year = String(word[0]) + String(word[1]) + String(word[2]) + String(word[3]);
    // String tmp;
    char tanzhen; //探针
    int Yue = 0;
    int ri = 0;
    if (word[6] != '-')
    {
        Yue = (word[5] - 48) * 10 + (word[6] - 48) ;
        if (word[9] != NULL)
        {
            ri = (word[8] - 48) * 10 + (word[9] - 48);
        }
        else{
          ri = (word[8] - 48);
          }
    }
    else if (word[6] == '-')
    {
      Yue =  word[5] - 48 ;
        if (word[8] != NULL)
        {
            ri = (word[7] - 48) * 10 + (word[8] - 48);
        }
        else {
          ri = word[7] - 48;
        }
    }
    Serial.println("月");
    Serial.println(Yue);
    Serial.println(ri);
    int str_num2[5] = {atoi(year.c_str()),
                       Yue,
                       ri,
                       time_now2022.hour(),
                       time_now2022.minute()};
    value_baoshi = 25;                                                                        //报时值，任意值
    rtc.adjust(DateTime(str_num2[0], str_num2[1], str_num2[2], str_num2[3], str_num2[4], 0)); //年 月 日 时 分钟 秒
    display_main(1);                                                                          //重新显示时间
    //previousMillis = millis();                                                                //读取当前时间
}
