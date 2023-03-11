/*
 * @Author: your name
 * @Date: 2022-03-07 21:15:28
 * @LastEditTime: 2022-03-07 22:15:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \radio\camera.hpp
 */
#ifndef CAMERA_H
#define CAMERA_H
#include <esp32cam.h>
#include <WebServer.h>
#include <WiFi.h>

extern const char *SSID;
extern const char *PASS;
extern WebServer server;
extern void handleMjpeg();
extern void Camera_Init();//1.摄像机管脚定义；2.客户端初始化 3.图像在 /cam
#endif // !CAMERA_H
