#include "main.h"
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

class Display
{
public:
    void display_init()
    {
        u8g2.begin();
        u8g2.enableUTF8Print();
        u8g2.setFont(u8g2_font_unifont_t_chinese3); // use chinese2 for all the glyphs of "你好世界"
        u8g2.setFontDirection(0);
    }
    void Car_init(String process, String state = " ")
    {
        u8g2.clearBuffer();
        u8g2.setCursor(0, 15);
        u8g2.print(String("初始化: ") + process);
        u8g2.setCursor(u8g2.getWidth() / 2 - state.length() / 4 * 10, 35);
        u8g2.print(state);
        u8g2.sendBuffer();
    }
    void Center(String info, int angle = 0)
    {
        // u8g2.setFontDirection(angle);
        u8g2.clearBuffer();
        u8g2.setCursor(u8g2.getWidth() / 2 - info.length() / 4 * 10, u8g2.getHeight() / 2);
        u8g2.print(info);
        u8g2.sendBuffer();
        // u8g2.setFontDirection(0);
    }
    void show_info(float angle ,float groy,float time,float ve)
    {
        // u8g2.setFontDirection(angle);
        u8g2.clearBuffer();
        u8g2.setCursor(0,15);
        u8g2.print("angle:"+String(angle));
         u8g2.setCursor(0,30);
        u8g2.print("x:"+String(groy));
        u8g2.setCursor(0,45);
        u8g2.print("vel:"+String(time));
        u8g2.setCursor(0,60);
        u8g2.print("balance:"+String(ve));
        u8g2.sendBuffer();
        // u8g2.setFontDirection(0);
    }
};