#include "oled.h"

const unsigned char PROGMEM logo_bmp[32] =
    {0b00000000, 0b11000000,
     0b00000001, 0b11000000,
     0b00000001, 0b11000000,
     0b00000011, 0b11100000,
     0b11110011, 0b11100000,
     0b11111110, 0b11111000,
     0b01111110, 0b11111111,
     0b00110011, 0b10011111,
     0b00011111, 0b11111100,
     0b00001101, 0b01110000,
     0b00011011, 0b10100000,
     0b00111111, 0b11100000,
     0b00111111, 0b11110000,
     0b01111100, 0b11110000,
     0b01110000, 0b01110000,
     0b00000000, 0b00110000};

void Display_init()
{

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
}

void Display(String data)
{
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(data);
  display.setCursor(10, 16);
  display.display(); // Show initial text
}

//*=    B   M   P   ===============================================*//
const unsigned char PROGMEM Cat[134] = {/* (28 X 32 )*/
                                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0x80, 0x73, 0xFF,
                                        0xFF, 0x80, 0x03, 0xFF, 0xFF, 0x38, 0x63, 0xFF, 0xFE, 0x44, 0xD9, 0xFF, 0xFE, 0x80, 0x09, 0xFF,
                                        0xFE, 0x81, 0x04, 0xFF, 0xFC, 0x81, 0x04, 0xFF, 0xFC, 0x81, 0x04, 0xFF, 0xFC, 0x85, 0x04, 0xFF,
                                        0xFE, 0xC9, 0x09, 0xFF, 0xFE, 0x70, 0xF9, 0xFF, 0xFF, 0x04, 0x63, 0xFF, 0xFF, 0x80, 0x07, 0xFF,
                                        0xFF, 0xE0, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const unsigned char PROGMEM Cat_2[640] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xF7, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xBF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x9F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xFF, 0xFF, 0x7F, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x7F,
    0xFF, 0xFF, 0x17, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x1F, 0xFF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xF7, 0x8F, 0xFF, 0xBF, 0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xC7, 0xFF, 0xDF,
    0xFF, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF7, 0xE1, 0xFF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xC0, 0x3F, 0xE7, 0xFF, 0xBF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0x00, 0x07, 0xFC, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0xF8,
    0x01, 0xFF, 0xBC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE3, 0xFC, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xE7, 0x0E, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEE, 0x06, 0x00, 0x00,
    0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCE, 0x06, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xDC, 0x06, 0x0F, 0x0F, 0xF7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9C, 0x06, 0x3F, 0x8F, 0xEF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x9C, 0x06, 0x79, 0xCF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9C, 0x0E,
    0xE0, 0xE7, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x9E, 0x1E, 0xC0, 0x67, 0xBF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x8F, 0x3D, 0xC0, 0x67, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xF9, 0x80, 0x66,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC7, 0xF1, 0x80, 0xE5, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xC1, 0xE1, 0xC0, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x01, 0xC1, 0xCF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x7D, 0xE3, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x3C,
    0xFF, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x38, 0x7F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFE, 0x30, 0x3E, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x7F,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFC, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x01, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x01, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
    0xFF, 0xFF, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0xFF, 0xFF, 0xF0, 0x7F, 0xFF, 0xFF,
    0xFF, 0xFF, 0xF0, 0x00, 0x7F, 0xFF, 0xEC, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x03, 0x1F,
    0xD4, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x1F, 0xDD, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF,
    0xF0, 0x00, 0x00, 0x1F, 0xC1, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x3F, 0xC4, 0x3F,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0xFF, 0xFF, 0xE0, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const unsigned char PROGMEM Cat_3[704] = {/* (82 X 64 )*/

                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x01, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0x00, 0x00, 0x02, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x3F, 0x00, 0x0C, 0x0F,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xC3, 0xC0, 0x18, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xE3, 0x00, 0xE0, 0x18, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0x00, 0x70, 0x30,
                                          0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x86, 0x00, 0x30, 0x30, 0x04, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFE, 0x0C, 0x00, 0x38, 0x30, 0x04, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x1C, 0x00, 0x38,
                                          0x30, 0x02, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x1C, 0x00, 0x1C, 0x30, 0x03, 0x3F, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xE0, 0x1C, 0x00, 0x1C, 0x30, 0x03, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x3C, 0x00,
                                          0x1C, 0x30, 0x03, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x3C, 0x00, 0x1E, 0x30, 0x03, 0x9F, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0x00, 0x3C, 0x00, 0x1E, 0x38, 0x03, 0xCF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x3E,
                                          0x00, 0x1E, 0x38, 0x03, 0xCF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x3E, 0x00, 0x1E, 0x3C, 0x03, 0xCF,
                                          0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x3E, 0x00, 0x3E, 0x3C, 0x07, 0xCF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
                                          0x3F, 0x00, 0x3E, 0x1F, 0x0F, 0xCF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x3F, 0x80, 0x7E, 0x1F, 0xFF,
                                          0xCF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x3F, 0xE1, 0xFE, 0x1F, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0x80,
                                          0xC0, 0x3F, 0xFF, 0xFE, 0x0F, 0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0x9F, 0xF8, 0x3F, 0xFF, 0xFC, 0x0F,
                                          0xFF, 0xCF, 0xFF, 0xFF, 0xFF, 0xCF, 0xF8, 0x1F, 0xFF, 0xFC, 0x0F, 0xFF, 0x8F, 0xFF, 0xFF, 0xFF,
                                          0xE7, 0xFC, 0x1F, 0xFF, 0xFC, 0x07, 0xFF, 0x8F, 0xFF, 0xFF, 0xFC, 0x01, 0xFC, 0x0F, 0xFF, 0xF8,
                                          0x03, 0xFF, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x7C, 0x0F, 0xFF, 0xF8, 0x01, 0xFE, 0x1F, 0xFF, 0xFF,
                                          0xE0, 0x00, 0x1E, 0x07, 0xFF, 0xF0, 0x00, 0xF8, 0x1F, 0xFF, 0xFF, 0xC0, 0x00, 0x06, 0x03, 0xFF,
                                          0xE0, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0x80, 0x00, 0x01, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x3F, 0xFF,
                                          0xFF, 0x80, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0x00, 0xFF, 0xFE, 0x00,
                                          0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF,
                                          0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
                                          0xC0, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x80, 0x7F, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x1F,
                                          0xFF, 0xFF, 0xFF, 0x80, 0x1F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0x80, 0x00,
                                          0x03, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0,
                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
                                          0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00,
                                          0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
                                          0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xC0, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x1F, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x08, 0x3F,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xF8, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                                          0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const unsigned char PROGMEM Erweima[512]={/* (64 X 64 )*/
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xC0,0x00,0x1E,0x3F,0xF3,0x98,0x00,0x01,0xC0,0x00,0x1E,0x3F,0xF3,0x98,0x00,0x01,
0xCF,0xFF,0x18,0x00,0x03,0x98,0xFF,0xF1,0xCF,0xFF,0x18,0x00,0x03,0x98,0xFF,0xF1,
0xCF,0xFF,0x18,0x00,0x03,0x98,0xFF,0xF1,0xCE,0x03,0x18,0x31,0xFF,0xF8,0xC0,0x31,
0xCE,0x03,0x18,0x31,0xFF,0xF8,0xC0,0x31,0xCE,0x03,0x18,0x31,0x83,0xF8,0xC0,0x31,
0xCE,0x03,0x18,0x31,0x83,0xF8,0xC0,0x31,0xCE,0x03,0x18,0x31,0x83,0xF8,0xC0,0x31,
0xCE,0x03,0x1F,0xFF,0xF3,0xF8,0xC0,0x31,0xCE,0x03,0x1F,0xFF,0xF3,0xF8,0xC0,0x31,
0xCF,0xFF,0x1F,0xFE,0x7F,0xF8,0xFF,0xF1,0xCF,0xFF,0x1F,0xFE,0x7F,0xF8,0xFF,0xF1,
0xC0,0x00,0x18,0xC6,0x73,0x98,0x00,0x01,0xC0,0x00,0x18,0xC6,0x73,0x98,0x00,0x01,
0xC0,0x00,0x18,0xC6,0x73,0x98,0x00,0x01,0xFF,0xFF,0xF8,0x3E,0x73,0x9F,0xFF,0xFF,
0xFF,0xFF,0xF8,0x3E,0x73,0x9F,0xFF,0xFF,0xCF,0xFF,0x18,0x31,0x8C,0x00,0xF8,0x0F,
0xCF,0xFF,0x18,0x31,0x8C,0x00,0xF8,0x0F,0xC0,0x7C,0x00,0x00,0x0C,0x00,0xE0,0x0F,
0xC0,0x7C,0x60,0x06,0x7C,0x03,0xC0,0x0F,0xC0,0x7C,0x60,0x06,0x7C,0x03,0xC0,0x0F,
0xC0,0x00,0x00,0xC6,0x00,0x78,0x39,0xC1,0xC0,0x00,0x00,0xC6,0x00,0x78,0x39,0xC1,
0xC0,0x00,0x00,0xC0,0x00,0x18,0x01,0xC1,0xF1,0x80,0x7F,0xC1,0xF0,0x1F,0xC1,0xF1,
0xF1,0x80,0x7F,0xC1,0xF0,0x1F,0xC1,0xF1,0xC0,0x0F,0x1F,0xC6,0x73,0x80,0xFF,0xF1,
0xC0,0x0F,0x1F,0xC6,0x73,0x80,0xFF,0xF1,0xCF,0xFF,0xE0,0x07,0x80,0x7F,0xFF,0xCF,
0xCF,0xFF,0xE0,0x07,0x80,0x7F,0xFF,0xCF,0xCF,0xFF,0xE0,0x07,0x80,0x7F,0xFF,0xCF,
0xCE,0x00,0x1F,0xF0,0x7C,0x63,0x39,0xC1,0xCE,0x00,0x1F,0xF0,0x7C,0x63,0x39,0xC1,
0xCE,0x63,0xE6,0x31,0xF3,0x9F,0xC6,0x31,0xCE,0x63,0xE6,0x31,0xF3,0x9F,0xC6,0x31,
0xCE,0x63,0xE6,0x31,0xF3,0x9F,0xC6,0x33,0xCE,0x60,0x18,0x31,0xFF,0x80,0x06,0x3F,
0xCE,0x60,0x18,0x31,0xFF,0x80,0x06,0x3F,0xFF,0xFF,0xF8,0xC6,0x0C,0x1F,0xC6,0x3F,
0xFF,0xFF,0xF8,0xC6,0x0C,0x1F,0xC6,0x3F,0xC0,0x00,0x18,0xC0,0x0C,0x1C,0xC0,0x33,
0xC0,0x00,0x1F,0xC1,0xFF,0x98,0xC1,0xF1,0xC0,0x00,0x1F,0xC1,0xFF,0x98,0xC1,0xF1,
0xCF,0xFF,0x1E,0x06,0x0F,0x9F,0xC7,0xC1,0xCF,0xFF,0x1E,0x06,0x0F,0x9F,0xC7,0xC1,
0xCE,0x03,0x1E,0x3E,0x70,0x00,0x00,0x01,0xCE,0x03,0x1E,0x3E,0x70,0x00,0x00,0x01,
0xCE,0x03,0x1E,0x3E,0x70,0x00,0x00,0x01,0xCE,0x03,0x1F,0xC7,0xF3,0xF8,0x39,0xC1,
0xCE,0x03,0x1F,0xC7,0xF3,0xF8,0x39,0xC1,0xCE,0x03,0x1E,0x30,0x7F,0xE3,0xFE,0x31,
0xCE,0x03,0x1E,0x30,0x7F,0xE3,0xFE,0x31,0xCE,0x03,0x1E,0x30,0x7F,0xE3,0xFE,0x31,
0xCF,0xFF,0x1F,0xC1,0xF0,0x18,0x07,0xF1,0xCF,0xFF,0x1F,0xC1,0xF0,0x18,0x07,0xF1,
0xC0,0x00,0x18,0x3F,0x80,0x18,0xF9,0xF1,0xC0,0x00,0x18,0x3F,0x80,0x18,0xF9,0xF1,
0xC0,0x00,0x18,0x3F,0xC0,0x1C,0xF9,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
};

const unsigned char PROGMEM wendu[1024]={
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xFF,0xDC,0x01,0xFD,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0x60,0xFF,0xDD,0xFC,0xC0,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xBF,0x7F,0xDD,0x9E,0xF9,0x7F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x3E,0xFC,0xBF,0x7F,0xDD,0x1E,0xFD,0x7F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xA0,0xFC,0x83,0x7F,0x8D,0xBC,0xFF,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xBC,0xFC,0x9D,0x7F,0xED,0xBC,0xE0,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xBC,0xFD,0xAD,0x7F,0xD9,0xBC,0xE5,0xEF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x30,0xFD,0xA5,0x7F,0xD8,0x0D,0xFD,0xCF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xB8,0xFD,0xBD,0x7F,0x9B,0x3D,0xFD,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xBC,0xFD,0xC0,0x7F,0x82,0x0D,0xFD,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xB9,0xFD,0xFC,0x7F,0x83,0x6D,0xFD,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xB9,0xFD,0xFE,0xFF,0xF7,0x09,0xFD,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x3D,0xFF,0xFF,0xFF,0xE7,0xF9,0xFD,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0xF9,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0xF9,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x1F,0xE3,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x23,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x05,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0x0F,0xE5,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0x23,0x26,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0x32,0x66,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0x38,0xE7,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0x38,0xE7,0xBF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0x30,0xE7,0xDF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0x26,0x67,0xCF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0x0E,0x07,0xE7,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0x1F,0x27,0xF7,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0x0F,0xC7,0xF3,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0x23,0x67,0xF8,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0x30,0xE3,0xFE,0x7F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0x38,0xE4,0xFF,0x3F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x32,0x27,0x07,0x87,0xFF,0xF1,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x27,0x07,0xE0,0x00,0x7C,0x07,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0x0F,0xC7,0xFE,0x00,0x00,0x6F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x0F,0xC7,0xFF,0xFF,0x07,0x83,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x27,0x27,0xFF,0xF8,0x3F,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x38,0x77,0xFF,0xC1,0x0F,0x7D,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x7F,0x3C,0x77,0xFF,0x0E,0x60,0x40,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x7F,0x30,0x27,0xF8,0x7C,0xFC,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0x23,0x87,0xE0,0x3D,0xC0,0x01,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0x07,0xE7,0x0D,0x81,0x00,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0x0F,0xE0,0x39,0xE0,0x00,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0xFE,0x3F,0xE1,0x0B,0x80,0x0F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFE,0x3F,0x8E,0xE4,0x00,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xFD,0x3E,0x1E,0xC0,0x07,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xF9,0x38,0x81,0x00,0x1F,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFB,0x23,0x78,0x00,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xF7,0x0E,0x60,0x07,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0x01,0xFF,0xFF,0xE7,0xF4,0x00,0x80,0x1F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0xFF,0xFF,0xE7,0xE0,0x38,0x00,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF3,0xFC,0xFF,0xFF,0xCF,0xC3,0x30,0x03,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0x3D,0x7F,0xFF,0xCF,0x83,0x00,0x07,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0x01,0xBF,0xFF,0x9E,0x18,0x00,0x67,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0xF9,0xCF,0xFF,0x1C,0xDC,0x01,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xD2,0x61,0xE3,0xFF,0x30,0x50,0x07,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x93,0x0D,0xF8,0x00,0x09,0x80,0x1F,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xB3,0x05,0xFE,0x00,0x1B,0x00,0x1F,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x32,0x40,0xFF,0xF0,0x74,0x00,0x3F,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x71,0xF8,0x01,0x00,0x00,0x0F,0x3F,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x70,0xFD,0x00,0x32,0x40,0x7F,0x3F,0xE7,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFE,0xFF,0x7D,0xFF,0xE6,0x81,0xFF,0x3F,0xEF,0xFF,0xFF,0xFF,0xFF,
};

const unsigned char PROGMEM Suiping[1024]={
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0xFF,0xFF,0xDF,0xFF,0xFF,0xFB,0xFD,0xFF,0xFF,
0xFF,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x7F,0xFF,0xDB,0xFC,0x07,0xFB,0xF9,0xFF,0xFF,
0xFF,0xFF,0xFC,0x00,0x1F,0xFE,0x00,0x3F,0xFE,0x13,0xF0,0x7F,0xF7,0x4B,0xFF,0xFF,
0xFF,0xFF,0xF8,0x00,0x03,0xFC,0x00,0x1F,0xF8,0x97,0xFE,0xFF,0xE7,0x4B,0xDF,0xFF,
0xFF,0xFF,0xF9,0x00,0x00,0x00,0x7C,0x1F,0xFF,0x87,0xFA,0xFF,0xE7,0x73,0xFF,0xFF,
0xFF,0xFF,0xFB,0xC0,0x00,0x00,0x0F,0x0F,0xFF,0x13,0xFA,0x5F,0xD7,0x37,0xFF,0xFF,
0xFF,0xFF,0xFB,0xE0,0x00,0x00,0x01,0xCF,0xFE,0x5B,0xFC,0x3F,0xB7,0xA7,0xFF,0xFF,
0xFF,0xFF,0xF9,0xF0,0x01,0x00,0x00,0x27,0xFC,0x9D,0xFE,0x07,0xE7,0x8F,0xFF,0xFF,
0xFF,0xFF,0xF9,0xF8,0x0F,0xE0,0x00,0x07,0xF9,0xBF,0xF0,0x7F,0xE7,0xCF,0xFF,0xFF,
0xFF,0xFF,0xFC,0xF8,0x3F,0xF0,0x0F,0xC7,0xFB,0xBF,0xFE,0xFF,0xEF,0x87,0xFF,0xFF,
0xFF,0xFE,0xFC,0xF8,0xC1,0xF0,0x0F,0xE3,0xFF,0xBF,0xFE,0xFF,0xEF,0x3F,0xFF,0xFF,
0xFF,0xFC,0x1C,0xF1,0x80,0xF8,0x1C,0x73,0xFF,0x3F,0xFE,0xFF,0xEE,0x7F,0xFF,0xFF,
0xFF,0xF8,0x0E,0xE1,0x00,0x78,0x18,0x33,0xFF,0x3F,0xFE,0xFF,0xFD,0xFF,0xFF,0xFF,
0xFF,0xF0,0x0E,0x60,0x00,0x7C,0x10,0x33,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x0E,0x42,0x00,0x3C,0x00,0x33,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x0E,0x02,0x00,0x3C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x1F,0x04,0x00,0x3C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xE0,0x1C,0x04,0x00,0x3C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xE0,0x39,0x84,0x00,0x3C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x31,0x84,0x00,0x3C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x21,0x84,0x00,0x3C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x21,0x84,0x00,0x7C,0x00,0x1B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF0,0x01,0x84,0x00,0x7C,0x00,0x3B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF8,0x01,0x86,0x00,0x7C,0x00,0x3B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFC,0x00,0x86,0x00,0xF8,0x00,0x3B,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFE,0x00,0xC3,0x01,0xF8,0x00,0x73,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFE,0x00,0x61,0xCF,0xF0,0x0F,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF8,0x80,0x60,0xFF,0xC0,0x07,0xC7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF3,0xC0,0x38,0x7F,0x80,0x03,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xE7,0xE0,0x1C,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xCC,0xF0,0x00,0x00,0x00,0x00,0x24,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDD,0xF8,0x00,0x03,0x80,0x00,0xC6,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0xFE,0x00,0x00,0xC0,0x01,0x87,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x9F,0xFF,0xC0,0x00,0x60,0x03,0x07,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xBF,0xFF,0xFF,0x80,0x10,0x08,0x07,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xBE,0x7F,0xF9,0xE0,0x07,0xFC,0x0D,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xBF,0xFC,0xFD,0xF0,0x0F,0xFE,0x0D,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x80,0xFD,0xFF,0xF8,0x0F,0x7F,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xC7,0x7F,0xFF,0xCC,0x1F,0x3F,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0x3F,0xF0,0xEE,0xFF,0xDF,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0x9F,0xFF,0xFF,0xF5,0xFF,0x18,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0xCF,0xFF,0xFF,0xFC,0x7C,0x7C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0xE0,0x3F,0xCF,0xFE,0x11,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0xF0,0x03,0xFF,0xF8,0x07,0xFD,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xDF,0xFF,0xF1,0xFF,0xF3,0xFF,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xCF,0xFF,0xF9,0xE1,0xE7,0xFF,0xF9,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xEF,0xFF,0xFC,0x00,0x0F,0xFF,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF7,0xFF,0xFF,0xFE,0x3F,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFE,0x3F,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0x8F,0xFF,0xFF,0xFF,0xF8,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xE1,0xFF,0xFF,0xFF,0xC3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFC,0x1F,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xC0,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF

};

const unsigned char PROGMEM Date[1024]={
  0xFF,0xFF,0xFF,0xFE,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFE,0xCF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x00,0x3F,0xFE,0xCF,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0x00,0x3F,0xFC,0x07,0x37,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,
0xFE,0xFF,0xBF,0xFE,0xCE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xFF,0xFF,0xFF,
0xFE,0xFF,0xBF,0xFE,0xCE,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x0F,0xFF,0xFF,0xFF,
0xFE,0xFF,0xBF,0xFC,0x0E,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x0F,0xFF,0xFF,0xFF,
0xFE,0xFF,0xBF,0xFC,0xDE,0x27,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x0F,0xFF,0xFF,0xFF,
0xFE,0xFF,0xBF,0xFC,0xDE,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x01,0xFF,0xFF,
0xFE,0x00,0x3F,0xFC,0x0E,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0xC0,0x00,0x1F,0xFF,
0xFE,0x00,0x3F,0xFC,0xCC,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xC3,0x80,0x00,0x01,0xFF,
0xFE,0xFF,0xBF,0xF8,0x04,0x07,0x7F,0xFF,0xFF,0xFF,0xFF,0x86,0x00,0x00,0x00,0x7F,
0xFE,0xFF,0xBF,0xFF,0x05,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0x9C,0x00,0x00,0x00,0x0F,
0xFE,0xFF,0xBF,0xFE,0x7D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0x30,0x00,0x00,0x00,0x03,
0xFE,0xEF,0xBF,0xFE,0x9D,0xEF,0xFF,0xFF,0xFF,0xFF,0xFF,0x60,0x00,0x00,0x00,0x01,
0xFE,0x00,0x3F,0xFC,0xC9,0xEF,0xFF,0xFF,0xFF,0xFF,0xFE,0xC0,0x00,0x00,0x00,0x00,
0xFE,0x00,0x3F,0xFD,0xEB,0xEF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x18,0x00,0x00,0x0C,0x10,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x18,0x00,0x00,0x04,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x10,0x0C,0x10,0x04,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x10,0x0C,0x30,0x04,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x30,0x0C,0x30,0x04,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x30,0x0C,0x38,0x06,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x30,0x0C,0x38,0x0C,0x3E,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x38,0x18,0x3C,0x0C,0x3D,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1C,0x38,0x1F,0x7C,0x39,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x1F,0xF0,0x0F,0xF8,0x33,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x0F,0xC0,0x07,0xF0,0x67,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x03,0xC0,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x10,0x00,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x01,0xF0,0x00,0x7F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x07,0xF0,0x00,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x07,0xF0,0x00,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x01,0xF0,0x01,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0xF0,0x01,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x70,0x07,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x20,0x0F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x1F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x3F,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x1F,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x0F,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x07,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x03,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x07,0xFC,0x00,0x0C,0x01,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x3F,0xE0,0x3C,0x00,0x08,0x00,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF9,0xC0,0xFF,0x00,0x00,0x18,0x00,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFE,0x03,0xF8,0x00,0x30,0x00,0x40,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xF8,0x1F,0x00,0x60,0x00,0x60,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0xFF,0xFF,0xC1,0xE0,0xC0,0x18,0x20,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFC,0x00,0x1C,0x80,0x7E,0x30,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0xFF,0xF0,0x00,0x07,0x80,0x03,0x90,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0xFF,0xE0,0x00,0x01,0xE0,0x01,0x88,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xFF,0xE0,0x00,0x00,0x38,0x00,0x88,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x7F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0xC0,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xCF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x01,0x80,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x01,0x00
};

const unsigned char PROGMEM heart[128]={
  0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x0F,0xFF,0xFF,0x80,0x03,0xFF,0xFF,0x80,0xC1,0xFF,
0xFF,0x07,0xFC,0x7F,0xFE,0x7F,0xFF,0x3F,0xFC,0xFF,0xC3,0xBF,0xFC,0x0F,0xFD,0x9F,
0xFD,0xF8,0xFC,0x1F,0xE0,0x00,0x00,0x4F,0xE7,0xFB,0xFB,0xCF,0xEF,0xEB,0xF9,0x87,
0xE7,0xEB,0xF9,0x37,0xF7,0xCD,0xF3,0xE7,0xF3,0xC5,0xE7,0xE7,0xFC,0x0E,0x0F,0xC7,
0xFD,0xCF,0xFF,0x97,0xFD,0xDF,0xFF,0x97,0xFC,0xDF,0xFF,0xF7,0xFE,0x9F,0xFF,0xF7,
0xFE,0x39,0xFF,0xE7,0xFE,0x03,0xFF,0xCF,0xFE,0x7F,0xFF,0x8F,0xFF,0x7F,0xFF,0x9F,
0xFF,0x7F,0xF9,0x9F,0xFF,0x3F,0xF1,0xDF,0xFF,0xBF,0xE3,0xDF,0xFF,0x0F,0xC7,0xDF,
0xFF,0xC0,0x7F,0xDF,0xFF,0xF9,0x7F,0xDF,0xFF,0xFD,0xFF,0xFF,0xFF,0xFD,0xBF,0xFF
};
//*=    B   M   P   ===============================================*//

//*=    汉    字   ===============================================*//
const unsigned char PROGMEM Shi_Zhong[][32] = {
    {0xFF, 0xF7, 0xFF, 0xF7, 0x83, 0xF7, 0xBB, 0xF7, 0xBA, 0x01, 0xBB, 0xF7, 0xBB, 0xF7, 0x83, 0xF7,
     0xBB, 0x77, 0xBB, 0xB7, 0xBB, 0xB7, 0xBB, 0xF7, 0x83, 0xF7, 0xBB, 0xF7, 0xFF, 0xD7, 0xFF, 0xEF, /*"时",0*/
     /* (16 X 16 , 宋体 )*/},
    {0xEF, 0xDF, 0xEF, 0xDF, 0xC3, 0xDF, 0xDF, 0xDF, 0xBE, 0x03, 0x42, 0xDB, 0xEE, 0xDB, 0xEE, 0xDB,
     0x02, 0xDB, 0xEE, 0x03, 0xEE, 0xDB, 0xEF, 0xDF, 0xEB, 0xDF, 0xE7, 0xDF, 0xEF, 0xDF, 0xFF, 0xDF, /*"钟",1*/
     /* (16 X 16 , 宋体 )*/}};

const unsigned char PROGMEM Bu_Shu[][32] = {
    {0xFE, 0xFF, 0xFE, 0xFF, 0xEE, 0x07, 0xEE, 0xFF, 0xEE, 0xFF, 0xEE, 0xFF, 0x00, 0x01, 0xFE, 0xFF,
    0xFE, 0xFF, 0xEE, 0xF7, 0xEE, 0xEF, 0xDE, 0xDF, 0xBF, 0x3F, 0xFC, 0xFF, 0xE3, 0xFF, 0x1F, 0xFF, /*"步",0*/
    /* (16 X 16 , 宋体 )*/},

    {0xF7, 0xDF, 0xB6, 0xDF, 0xD5, 0xDF, 0xF7, 0xC1, 0x00, 0xBB, 0xD5, 0xBB, 0xB6, 0xBB, 0x77, 0x5B,
    0xEF, 0xD7, 0x01, 0xD7, 0xDD, 0xEF, 0xBD, 0xEF, 0x9B, 0xD7, 0xE7, 0xD7, 0xCB, 0xBB, 0x3D, 0x7D, /*"数",1*/
    /* (16 X 16 , 宋体 )*/}

};