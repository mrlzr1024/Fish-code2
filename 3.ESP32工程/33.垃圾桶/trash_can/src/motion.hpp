#include <Arduino.h>
class Motion
{
    /*
     * 类名：Motion
     * 作用：计算步进电机脉冲数，舵机角度
     */
private:
    int X = 0, Y = 0;
    int length_x = 0;
    float pi = 3.1415962;
    struct
    {
        int Length_y;
        float radian_y;
    } En_y;
    struct
    {
        int Server_angle_1,
            Server_angle_2;
        int server1_support = 0;
        int server2_support = 0;
        int len_1, len_2;
        int shadow;
        int deep;
    } arm;

public:
    Motion(int ly, int arm_a, int arm_b, int deep, int Sangle1, int Sangle2)
    {
        /**
         * @brief 初始化参数
         * ly:y轴杆长
         * arm_a:机械臂上杆长
         * arm_b:机械臂下杆长
         * deep：设定的下降深度(z坐标)
         * Sangle1:机械臂上舵机角度偏置
         * Sangle2:机械臂下舵机角度偏置
         */
        arm.server1_support = Sangle1;
        arm.server2_support = Sangle2;
        arm.len_1 = arm_a;
        arm.len_2 = arm_b;
        En_y.Length_y = ly;

        arm.shadow = sqrt(pow(arm.len_1, 2) - pow(deep - arm.len_2, 2));
    }
    void Set_Pi(float my_pi)
    {
        // sin 函数对应的参数是弧度值，并非角度值；弧度和角度相互转换原理：弧度 = 角度 * pi / 180.0；
        this->pi = my_pi;
    }
    void Calculation_whole(int X, int Y)
    {
        /**
         * @brief 初始化各项参数
         *
         */
        this->X = X;
        this->Y = Y;
        En_y.radian_y = int(acos(-Y / sqrt(pow(En_y.Length_y, 2) + pow(arm.shadow, 2))) - acos(arm.shadow / sqrt(pow(En_y.Length_y, 2) + pow(arm.shadow, 2))));
    }
    int Calculation_X_axis()
    {
        length_x = this->X - En_y.Length_y * cos(En_y.radian_y) - arm.shadow * sin(En_y.radian_y);
        return length_x;
    }
    float Calculation_Y_radian()
    {
        return En_y.radian_y;
    }
    float Calculation_z_1()
    {
        /**
         * @brief 计算机械臂上舵机[弧度]
         *
         */
        return pi - acos((arm.deep - arm.len_2) / arm.len_1);
    }
    float Calculation_z_2()
    {
        /**
         * @brief 计算机械臂下舵机[弧度]
         *
         */
        return pi / 2 + asin((arm.deep - arm.len_2) / arm.len_1);
    }
    int Conversion_to_angle(float radian)
    {
        return radian * 180 / pi;
    }
};