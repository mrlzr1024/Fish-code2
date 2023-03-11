/*
 * @Author: your name
 * @Date: 2022-03-06 11:45:31
 * @LastEditTime: 2022-06-02 19:50:49
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
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
#include "camera.hpp"
const int output = 4;
//HTML框架修改位置：629(索引)
void setup()
{
    Camera_Init();
	pinMode(output, OUTPUT);
    //设置初始值为低电平
    digitalWrite(output, LOW);
    // Server_web();
    server.begin();
}
void loop()
{
    server.handleClient();
}
