 
#include <TFT_eSPI.h>             
TFT_eSPI tft = TFT_eSPI();         
 
#include <HTTPClient.h>
#include <WiFi.h>
WiFiClient client;
 
#include "pngle.h"
 
#define WIFI_SSID "Davinci"
#define WIFI_PASS "shiwoya132"
 
// ===================================================
// pngle example for TFT_eSPI
// ===================================================
 
double g_scale = 1.0;
// pngle callback, called during decode process for each pixel
void pngle_on_draw(pngle_t *pngle, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t rgba[4])
{
  // Convert to RGB 565 format
  uint16_t color = tft.color565(rgba[0], rgba[1], rgba[2]);
 
  // If alpha > 0 then draw
  if (rgba[3]) {
    if (g_scale <= 1.0) tft.drawPixel(x, y, color);
    else {
      x = ceil(x * g_scale);
      y = ceil(y * g_scale);
      w = ceil(w * g_scale);
      h = ceil(h * g_scale);
      tft.fillRect(x, y, w, h, color);
    }
  }
 
}
 
void load_png(const char *url, double scale = 1.0)
{
  HTTPClient http;
  http.begin(client,url);
 
  int httpCode = http.GET();
  if (httpCode != HTTP_CODE_OK) {
    tft.printf("HTTP ERROR: %u\n", httpCode);
    http.end();
    return ;
  }
 
  int total = http.getSize();
 
  WiFiClient *stream = http.getStreamPtr();
 
  pngle_t *pngle = pngle_new();
  pngle_set_draw_callback(pngle, pngle_on_draw);
  g_scale = scale;
 
  uint8_t buf[2048];
  int remain = 0;
  uint32_t timeout = millis();
  while (http.connected()  && (total > 0 || remain > 0)) {
 
    // Break out of loop after 10s
    if ((millis() - timeout) > 10000UL)
    {
      tft.printf("HTTP request timeout\n");
      break;
    }
 
    size_t size = stream->available();
 
    if (!size) { delay(1); continue; }
 
    if (size > sizeof(buf) - remain) {
      size = sizeof(buf) - remain;
    }
 
    int len = stream->readBytes(buf + remain, size);
    if (len > 0) {
      int fed = pngle_feed(pngle, buf, remain + len);
      if (fed < 0) {
        tft.printf("ERROR: %s\n", pngle_error(pngle));
        break;
      }
      total -= len;
      remain = remain + len - fed;
      if (remain > 0) memmove(buf, buf + fed, remain);
    } else {
      delay(1);
    }
  }
 
  pngle_destroy(pngle);
 
  http.end();
}
// ===================================================
 
void setup()
{
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3); 
  tft.fillScreen(TFT_GREEN);
  tft.setTextColor(TFT_BLUE);
  tft.setTextFont(2);
  tft.printf("Welcome.\n");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(500);}
  tft.printf("WiFi connected.\n");
  delay(1000);
}
 
void loop()
{
  long t;
  t = micros();
  load_png("https://pngimg.com/uploads/monkey/monkey_PNG18737.png");
  delay(2000);
  load_png("http://www.joindesign.cn/2.png");
  delay(2000);
  load_png("http://www.joindesign.cn/3.png");
  delay(2000);
  load_png("http://www.joindesign.cn/4.png");
  delay(2000);
//   load_png("http://www.joindesign.cn/5.png");
//   delay(2000);
//   load_png("http://www.joindesign.cn/6.png");
//   delay(2000);
//   load_png("http://www.joindesign.cn/7.png");
//   delay(2000);
//   load_png("http://www.joindesign.cn/8.png");
//   delay(2000);
//   load_png("http://www.joindesign.cn/9.png");
//   delay(2000);
//   load_png("http://www.joindesign.cn/10.png");
  delay(2000);
  t = ( micros() -t - 20000000) / 1000; // (扣除显示延时)单位微秒，除1000后单位毫秒
  
  tft.fillScreen(TFT_GREEN);
  tft.setTextColor(TFT_BLUE);
  tft.setCursor(30,10);
  tft.setTextFont(4);
  tft.print(t); // 显示10张图的总加载时间， 大概10秒左右
 
  delay(5000);
  
}