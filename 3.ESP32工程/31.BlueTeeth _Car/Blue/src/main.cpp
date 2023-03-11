
//#include <BleKeyboard.h>
#include <Arduino.h>
#include <Versatile_RotaryEncoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"

// Set here your encoder reading pins (Ex.: EC11 with breakout board)
#define clk 15 // (A3)
#define dt 21  // (A4)
#define sw 4   // (A5)

#define R1 32
#define R2 33
#define R3 25
#define R4 26
#define R5 27

#define L1 19
#define L2 18

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// BleKeyboard bleKeyboard;

BluetoothSerial SerialBT;

uint8_t address[6] = {0x40, 0x22, 0xD8, 0x57, 0xEA, 0x0E}; //从机MAC地址 不同的蓝牙地址不同 需要自己修改

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

// Functions prototyping to be handled on each Encoder Event
void handleRotate(int8_t rotation);
void handlePressRotate(int8_t rotation);
void handleHeldRotate(int8_t rotation);
void handlePress();
void handlePressRelease();
void handleLongPress();
void handleLongPressRelease();
void handlePressRotateRelease();
void handleHeldRotateRelease();

// Create a global pointer for the encoder object
Versatile_RotaryEncoder *versatile_encoder;
enum Mode
{
    MUSIC,
    WORK
} now_mode;
void setup()
{

    Serial.begin(115200);
    pinMode(R1, INPUT_PULLUP);
    pinMode(R2, INPUT_PULLUP);
    pinMode(R3, INPUT_PULLUP);
    pinMode(R4, INPUT_PULLUP);
    pinMode(R5, INPUT_PULLUP);

    pinMode(L2, INPUT_PULLUP);
    pinMode(L1, INPUT_PULLUP);
    if (!display.begin(SSD1306_SWITCHCAPVCC))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    //===蓝牙=========================//
    Serial.println("Starting BLE work!");
    // bleKeyboard.begin();
    SerialBT.begin("ESP32_MASTER", true); //开启蓝牙 名称为:"ESP32_MASTER" 主机
    Serial.printf("Init Complete - Master\r\n");
    SerialBT.connect(address);
    //===蓝牙=========================//

    versatile_encoder = new Versatile_RotaryEncoder(clk, dt, sw);

    // Load to the encoder all nedded handle functions here (up to 9 functions)
    versatile_encoder->setHandleRotate(handleRotate);
    versatile_encoder->setHandlePressRotate(handlePressRotate);
    versatile_encoder->setHandleHeldRotate(handleHeldRotate);
    versatile_encoder->setHandlePress(handlePress);
    versatile_encoder->setHandlePressRelease(handlePressRelease);
    versatile_encoder->setHandleLongPress(handleLongPress);
    versatile_encoder->setHandleLongPressRelease(handleLongPressRelease);
    versatile_encoder->setHandlePressRotateRelease(handlePressRotateRelease);
    versatile_encoder->setHandleHeldRotateRelease(handleHeldRotateRelease);
    Serial.println("Ready!");
    // set your own defualt values (optional)
    // versatile_encoder->setReadIntervalDuration(1); // set 2ms as long press duration (default is 1ms)
    // versatile_encoder->setShortPressDuration(35); // set 35ms as short press duration (default is 50ms)
    // versatile_encoder->setLongPressDuration(550); // set 550ms as long press duration (default is 1000ms)
    now_mode = WORK;
    Display("Working....");
}

void loop()
{

    // Do the encoder reading and processing
    if (versatile_encoder->ReadEncoder())
    {
        // bleKeyboard.print("Hello world");
        //  Do something here whenever an encoder action is read
    }
    if (digitalRead(L2) == LOW)
    {
        delay(50);
        // while (digitalRead(L2) == LOW)
        //     ;
        SerialBT.write(0x02);
        Serial.println("L1");
        Display("notes");
    }
    else if (digitalRead(L1) == LOW)
    {
        delay(50);
        // while (digitalRead(L1) == LOW)
        //     ;
        SerialBT.write(0x01);
        Serial.println("L1");

        Display("format");
    }
}
int th = 5;
void handleRotate(int8_t rotation)
{
    Serial.print("#1 Rotated: ");
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 0);
    if (rotation < 0)
    {
        Serial.println("for");
        SerialBT.write(0x04);
        display.println("Down");
    }
    else
    {
        Serial.println("back");
        SerialBT.write(0x05);
        display.println("UP");
    }
    display.setTextSize(1);
    for (int i = 0; i < th; i++)
    {

        display.print('-');
        Serial.println(rotation);
        Serial.println(th);
    }
    display.setTextSize(2);
    display.display();
}

void handlePressRotate(int8_t rotation)
{
    Serial.print("#2 Pressed and rotated: ");
}

void handleHeldRotate(int8_t rotation)
{
    Serial.print("#3 Held and rotated: ");
}

void handlePress()
{
    Serial.println("#4 Pressed");
    SerialBT.write(0x03);
}

void handlePressRelease()
{
    Serial.println("#5 Press released");
}

void handleLongPress()
{
    Serial.println("#6 Long pressed");
}

void handleLongPressRelease()
{
    Serial.println("#7 Long press released");
}

void handlePressRotateRelease()
{
    Serial.println("#8 Press rotate released");
}

void handleHeldRotateRelease()
{
    Serial.println("#9 Held rotate released");
}

/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x32 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
