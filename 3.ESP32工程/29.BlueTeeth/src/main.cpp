
#include <BleKeyboard.h>
#include <Arduino.h>
#include <Versatile_RotaryEncoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

BleKeyboard bleKeyboard;
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
    bleKeyboard.begin();
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
    if (bleKeyboard.isConnected())
    {
        if (versatile_encoder->ReadEncoder())
        {
            // bleKeyboard.print("Hello world");
            //  Do something here whenever an encoder action is read
        }
        if (digitalRead(L2) == LOW)
        {
            delay(100);
            while (digitalRead(L2) == LOW)
                ;
            Serial.println("注释");
            bleKeyboard.press(KEY_RIGHT_CTRL);
            bleKeyboard.press('/');
            delay(100);
            bleKeyboard.releaseAll();
            Display("notes");
        }
        else if (digitalRead(L1) == LOW)
        {
            delay(100);
            while (digitalRead(L1) == LOW)
                ;
            Serial.println("格式化");
            bleKeyboard.press(KEY_RIGHT_SHIFT);
            bleKeyboard.press(KEY_RIGHT_ALT);
            bleKeyboard.press('F');
            delay(100);
            bleKeyboard.releaseAll();
            Display("format");
        }
        else if (digitalRead(R1) == LOW)
        {
            delay(100);
            while (digitalRead(R1) == LOW)
                ;
            Serial.println("复制");
            bleKeyboard.press(KEY_RIGHT_CTRL);
            bleKeyboard.press('c');
            delay(100);
            bleKeyboard.releaseAll();
            Display("Copy");
        }
        else if (digitalRead(R2) == LOW)
        {
            delay(150);
            while (digitalRead(R2) == LOW)
                ;

            Serial.println("粘贴");
            bleKeyboard.press(KEY_RIGHT_CTRL);
            bleKeyboard.press('v');
            delay(100);
            bleKeyboard.releaseAll();
            Display("Put");
        }
        else if (digitalRead(R3) == LOW)
        {
            delay(150);
            Serial.println("Ctrl");
            bleKeyboard.press(KEY_RIGHT_CTRL);

            while (digitalRead(R3) == LOW)
                ;
            bleKeyboard.releaseAll();
        }
        else if (digitalRead(R4) == LOW)
        {
            delay(150);
            while (digitalRead(R4) == LOW)
                ;

            Serial.println("休眠");
            // bleKeyboard.press(KEY);
            
            bleKeyboard.press('v');
            delay(100);
            bleKeyboard.releaseAll();
            Display("Put");
        }
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
    if (rotation > 0)
    {
        Serial.println("Right");
        bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
        display.println("Down");
    }
    else
    {
        Serial.println("Left");
        bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
        display.println("UP");
    }

    th -= rotation;
    if (th < 0)
        th = 0;
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
    if (rotation < 0)
    {
        Serial.println("Right");
        Serial.println("下一首");
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_LEFT_ALT);
        bleKeyboard.press(KEY_F3);
        delay(100);
        bleKeyboard.releaseAll();
        Display("Next");
    }
    else
    {
        Serial.println("Left");
        Serial.println("上一首");
        bleKeyboard.press(KEY_LEFT_CTRL);
        bleKeyboard.press(KEY_LEFT_ALT);
        bleKeyboard.press(KEY_F2);
        delay(100);
        bleKeyboard.releaseAll();
        Display("Last");
    }
}

void handleHeldRotate(int8_t rotation)
{
    Serial.print("#3 Held and rotated: ");
    if (rotation > 0)
        Serial.println("Right");
    else
        Serial.println("Left");
}

void handlePress()
{
    Serial.println("#4 Pressed");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
}

void handlePressRelease()
{
    Serial.println("#5 Press released");
}

void handleLongPress()
{
    Serial.println("#6 Long pressed");
    Serial.println("L2模式");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_SHIFT);
    bleKeyboard.press(KEY_F2);
    delay(100);
    bleKeyboard.releaseAll();
    Display("L2");
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
