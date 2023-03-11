#include <Arduino.h>
class Arm
{
    /**
     * @brief 机械臂部分角度/弧度计算
     * 输入：
     *      1.机械臂上臂长a
     *      2.机械臂下臂长b
     *      3.x,deep
     * 单位：cm
     */
private:
    float a = 0, b = 0, c = 0;
    float Rad_1 = 0, Rad_2 = 0, Rad_3 = 0;
    int Angle_1 = 0, Angle_2 = 0;
    float deep = 0, x = 0;
    float pi = asin(1) * 2;

public:
    void Set_Param(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
    bool Set_target(float deep, float x)
    {
        if (deep + abs(x) > a + b)
        {
            return false;
        }
        this->deep = deep;
        this->x = x;
        this->c = sqrt(pow(x, 2) + pow(deep, 2));
        if (min(a, b) + c < max(a, b))
        {
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
        Rad_3 = pi / 2 - atan(deep / x)-(x/180.0*pi);
        // Serial.printf("R3=%d \n",int(Rad_3*180/pi));
        // Serial.println("");
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