#include "Level_1.h"
void Clock_Interface();
void Step_Interface();
void Heart_Interface();
void Gradienter_Interface();
void TEmperature_Interface();
void Date_Interface();
void WLAN_Interface();
void Network_Interface();
void Advance_Interface();

Level_1_Control level_1_Control;

void handleRotate(int8_t rotation)
{

    if (level_1_Control == Standard)
    {
        int R = 0;
        Clock_switch = false;
        Rotation[0] += rotation; //  ==>
        if (Rotation[0] < 0)
        {
            R = -Rotation[0];
        }
        else
        {
            R = Rotation[0];
        }
        switch (R)
        {
        case 0:
            Clock_Interface();
            Mode_1 = Clock;
            break;
        case 1:
            Step_Interface();
            Mode_1 = Step;
            break;
        case 2:
            Heart_Interface();
            Mode_1 = Heart_Rate;
            break;
        case 3:
            Gradienter_Interface();
            Mode_1 = Gradienter;
            break;
        case 4:
            TEmperature_Interface();
            Mode_1 = TEmperature;
            break;
        case 5:
            Date_Interface();
            Mode_1 = DATE;
            break;
        case 6:
            WLAN_Interface();
            Mode_1 = WLAN;
            break;
        // case 7:
        //     Network_Interface();
        //     Mode_1 = Network;
        //     break;
        // case 8:
        //     Advance_Interface();
        //     Mode_1 = Advance;
        //     break;
        default:
            Rotation[0] = 0;
            handleRotate(0);
            break;
        }
    }
    else if (level_1_Control == second_Adjust)
    {
        Loop.second += rotation;
        if (Loop.second < 0)
        {
            Loop.second = 0;
        }
        Clock_total();
    }
    else if (level_1_Control == Minuse_Adjust)
    {
        Loop.minuse += rotation;
        if (Loop.minuse < 0)
        {
            Loop.minuse = 0;
        }
        Clock_total();
    }
    else if (level_1_Control == Hour_Adjust)
    {
        Loop.hour += rotation;
        if (Loop.hour < 0)
        {
            Loop.hour = 0;
        }
        Clock_total();
    }
    else if (level_1_Control == Date_Adjust)
    {
        Loop.day += rotation;
        if (Loop.day < 0)
        {
            Loop.day = 0;
        }
        Date_detect();
    }
    else if (level_1_Control == Mounth_Adjust)
    {
        Loop.mounth += rotation;
        if (Loop.mounth < 0)
        {
            Loop.mounth = 0;
        }
        Date_detect();
    }
    else if (level_1_Control == Year_Adjust)
    {
        Loop.year += rotation;
        if (Loop.year < 0)
        {
            Loop.year = 0;
        }
        Date_detect();
    }
}

void Clock_Interface()
{
    display.clearDisplay();
    display.drawBitmap(0, 0, Cat_2, 76, 64, 1);
    display.drawBitmap(78, 0, Shi_Zhong[0], 16, 16, 1);
    display.drawBitmap(78, 16, Shi_Zhong[1], 16, 16, 1);
    display.display();
}

void Step_Interface()
{
    display.clearDisplay();
    display.drawBitmap(0, 0, Cat_3, 82, 64, 1);
    display.drawBitmap(84, 0, Bu_Shu[0], 16, 16, 1);
    display.drawBitmap(84, 16, Bu_Shu[1], 16, 16, 1);
    display.display();
}

void Heart_Interface()
{
    display.clearDisplay();
    display.drawBitmap(128-32, 0, heart, 32, 32, 1);
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(1);
    display.setCursor(0, 0);
    display.println("Heart_Interface");
    display.setCursor(64, 32);
    display.println(abs(Rotation[0]));
    display.setTextColor(1);
    display.display();
}

void Gradienter_Interface()
{
    display.clearDisplay();
     display.drawBitmap(0, 0, Suiping, 128, 64, 1);
    display.setTextSize(1); // Draw 2X-scale text
    display.setCursor(75, 16);
    display.setTextColor(0);
    display.println("Gradienter");
    display.setCursor(64, 32);
    display.println(abs(Rotation[0]));
    display.setTextColor(1);
    display.display();
}

void TEmperature_Interface()
{
    display.clearDisplay();
    display.drawBitmap(0, 0, wendu, 128, 64, 1);
    display.setTextSize(1); // Draw 2X-scale text
    display.setCursor(0, 0);
    display.setTextColor(0);
    display.println("Temperature");
    display.setCursor(64, 32);
    display.println(abs(Rotation[0]));
    display.setTextColor(1);
    display.display();
}

void Date_Interface()
{
    display.clearDisplay();
    display.drawBitmap(0, 0, Date, 128, 64, 1);
    // display.setTextSize(2); // Draw 2X-scale text
    // display.setCursor(0, 0);
    // display.println("Date_Interface");
    // display.setCursor(64, 32);
    display.println(abs(Rotation[0]));
    display.display();
}

void WLAN_Interface()
{
    display.clearDisplay();
    display.drawBitmap(0, 0, Erweima, 64, 64, 1);
    display.display();
}

void Network_Interface()
{
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(0, 0);
    display.println("Network_Interface");
    display.setCursor(64, 32);
    display.println(abs(Rotation[0]));
    display.display();
}

void Advance_Interface()
{
    display.clearDisplay();
    display.setTextSize(2); // Draw 2X-scale text
    display.setCursor(0, 0);
    display.println("Advance_Interface");
    display.setCursor(64, 32);
    display.println(abs(Rotation[0]));
    display.display();
}




