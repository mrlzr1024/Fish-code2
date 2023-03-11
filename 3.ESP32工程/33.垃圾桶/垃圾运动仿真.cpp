#include <iostream>
#include<graphics.h>
#include <ctime>
using namespace std;
#define PI asin(1) * 2

void   Delay(int   time);

class Arm
{
private:

    float Rad_1 = 0, Rad_2 = 0, Rad_3 = 0;
    int Angle_1 = 0, Angle_2 = 0;
    float deep = 0, x = 0;
    float pi = asin(1) * 2;

public:
    float a = 0, b = 0, c = 0;
    void Set_Param(int a, int b)
    {
        this->a = a;
        this->b = b;

    }
    bool Set_target(float deep, float x)
    {
        if (deep + abs(x) > a + b) {
            return false;
        }
        this->deep = deep;
        this->x = x;
        this->c = sqrt(pow(x, 2) + pow(deep, 2));
        if (min(a, b) + c < max(a, b)) {
            return false;
        }
        return true;
    }
    void Calculation()
    {
        float i = acos((c * c + a * a - b * b) / (2 * a * c)) * 180 / pi;
        float j = atan(x / deep) * 180 / pi;
        if (x >= 0)
            Rad_1 = pi / 2 + atan(x / deep) - acos((c * c + a * a - b * b) / (2 * a * c));
        else // x<0
        {
            x = -x;
            Rad_1 = pi / 2 - atan(x / deep) - acos((c * c + a * a - b * b) / (2 * a * c));
        }
        i = Rad_1 * 180 / pi;
        Rad_2 = pi - acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
        Rad_3 = pi / 2 - atan(deep / x);
    }
    float Get_Rad_1()
    {
        return Rad_1;
    }
    float Get_Rad_2()
    {
        return Rad_2;
    }
    float Get_Rad_3()
    {
        return Rad_3;
    }
    int To_Angle(float Rad)
    {
        return Rad * 180.0 / pi;
    }
};
float Xita1, Xita2, Xita3;
float a, b, c, d;
float x_0 = 320, y_0 = 190;
float la = 150, lb = 150;
TCHAR text[20];
int main()
{
    initgraph(640, 640);
    settextstyle(10, 0, _T("华文新魏"));//设置字号、字体
    setlinecolor(WHITE);
    line(x_0, y_0, x_0 + 300, y_0);

    Arm My_arm;
    My_arm.Set_Param(15, 15);
    la = My_arm.a * 10;
    lb = My_arm.b * 10;
    for (int j = 0; j <= 22; j += 1) {
        _stprintf_s(text, _T("%d"), j);
        outtextxy(0, j * 10 + y_0, text);
        setlinecolor(WHITE);
        line(x_0 + 300, y_0 + j * 10, x_0 - 300, y_0 + j * 10);
        for (int i = -25; i <= 25; i += 1) {
            if (!My_arm.Set_target(j, i)) {
                setlinecolor(YELLOW);
                line(x_0 + i * 10, y_0 + j * 10, x_0 + i * 10, y_0 + j * 10 + 10);
                //system("pause");
                continue;
            }
            //My_arm.Set_target(26, 6);
            My_arm.Calculation();
            Xita1 = My_arm.Get_Rad_1();
            Xita2 = My_arm.Get_Rad_2();
            /*cout <<My_arm.Get_Rad_1() << endl;*/
            cout << "x= " << i << endl;
            cout << "Xita1= " << My_arm.To_Angle(Xita1) << endl;
            cout << "Xita2= " << My_arm.To_Angle(Xita2) << endl;
            cout << "==================" << endl;
            a = x_0 + la * cos(Xita1);
            b = y_0 + la * sin(Xita1);
            setlinecolor(LIGHTBLUE);
            line(x_0, y_0, a, b);
            if (Xita1 >= 0) {
                Xita3 = PI - Xita1 - Xita2;
                c = a - lb * cos(Xita3);
                d = b + lb * sin(Xita3);
            }
            else {
                Xita3 = Xita2 + Xita1 - PI / 2;
                c = a - lb * sin(Xita3);
                d = b + lb * cos(Xita3);
            }
            setlinecolor(LIGHTRED);
            line(a, b, c, d);
            setlinecolor(CYAN);
            line(c, d, c, d + 10);
            Delay(100);

        }
        //system("pause");
        cleardevice();
        setlinecolor(GREEN);
        line(x_0 + 300, y_0 + j * 10, x_0 - 300, y_0 + j * 10);

    }
    system("pause");
    closegraph();//关闭当前画布
    //cout << acos(4 / 5.0)*180/ (asin(1) * 2);
    //cout << 0.6-1000*(8.85 * 50 * 0.6 * pow(10, -6) / (0.6 * 0.25 + 8.85 * 50 * pow(10, -3)));
}



void   Delay(int   time)//time*1000为秒数 
{
    clock_t   now = clock();

    while (clock() - now < time);
}

