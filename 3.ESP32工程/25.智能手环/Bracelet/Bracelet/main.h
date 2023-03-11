#ifndef __MAIN_H
#define __MAIN_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //画图库
#include <Adafruit_SSD1306.h>
#include "encode.h"
#include "Temp.hpp"
#include "Timer.h"
#include "oled.h"
#include "Eeprom.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI 18 // D1
#define OLED_CLK 5   // D0
#define OLED_DC 16
#define OLED_CS 4
#define OLED_RESET 17

extern Adafruit_SSD1306 display;
extern void Display(String data);

class Bracelet
{
public:
    int second = 0;
    int minuse = 0;
    int hour = 0;
    int day = 10;
    int mounth = 7;
    int year = 2022;
    Bracelet(int second = 0,
             int minuse = 0,
             int hour = 0,
             int day = 10,
             int mounth = 7,
             int year = 2022) : second(second),
                             minuse(minuse),
                             hour(hour),
                             day(day),
                             mounth(mounth),
                             year(year)
    {
    }
};

extern Bracelet Loop;
#endif