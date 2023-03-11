/*
 * @Author: your name
 * @Date: 2022-03-04 07:42:17
 * @LastEditTime: 2022-03-04 07:58:26
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \WifiCam\WifiCam.hpp
 */
#ifndef WIFICAM_H
#define WIFICAM_H

#include <WebServer.h>
#include <esp32cam.h>

extern esp32cam::Resolution initialResolution;

extern WebServer server;

void addRequestHandlers();

#endif // WIFICAM_H
