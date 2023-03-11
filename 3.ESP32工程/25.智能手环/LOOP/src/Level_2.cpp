#include "Level_2.h"

void DISPLAY_s(String Data);
void Time_Adjust();
void Date_Adjust_();

void handlePressRotate(int8_t rotation)
{
    Rotation[1] += rotation; //    +==>
    switch (Mode_1)
    {
    case Clock:
        Time_Adjust();
        break;
    case DATE:
        Date_Adjust_();
        break;
    case Step:
        step = 0;
        Step_detect();
        break;
    default:
        break;
    }
}
void Time_Adjust()
{
    switch (Rotation[1])
    {
    case 1:
        level_1_Control = second_Adjust;
        DISPLAY_s("second_Adjust");
        break;
    case 2:
        level_1_Control = Minuse_Adjust;
        DISPLAY_s("Minuse_Adjust");
        break;
    case 3:
        level_1_Control = Hour_Adjust;
        DISPLAY_s("Hour_Adjust");
        break;
    default:
        Rotation[1] = 0;
        level_1_Control = Standard;
        DISPLAY_s("Standard");
        break;
    }
}
void Date_Adjust_()
{
    switch (Rotation[1])
    {
    case -1:
        level_1_Control = Date_Adjust;
        DISPLAY_s("Date_Adjust");
        break;
    case -2:
        level_1_Control = Mounth_Adjust;
        DISPLAY_s("Mounth_Adjust");
        break;
    case -3:
        level_1_Control = Year_Adjust;
        DISPLAY_s("Year_Adjust");
        break;
    default:
        Rotation[1] = 0;
        level_1_Control = Standard;
        DISPLAY_s("Standard");
        break;
    }
}
void DISPLAY_s(String Data)
{
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(0, 0);
    display.println(Data);
    display.display();
}