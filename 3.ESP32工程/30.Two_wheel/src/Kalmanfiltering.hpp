#include <MPU6050_tockn.h>
#include <Wire.h>
/*
 * 卡尔曼滤波
 * 使用库：
 *      tockn/MPU6050_tockn@^1.5.2
 * 注意：
 *  专门用于MPU6050
 */
class Kalman_filtering
{
private:
    /*计算偏移量*/
    float i;                            //计算偏移量时的循环次数
    float ax_offset = 0, ay_offset = 0; // x,y轴的加速度偏移量
    float gx_offset = 0, gy_offset = 0; // x,y轴的角速度偏移量

    /*参数*/
    float rad2deg = 57.29578;      //弧度到角度的换算系数
    float roll_v = 0, pitch_v = 0; //换算到x,y轴上的角速度

    /*定义微分时间*/
    float now = 0, lasttime = 0, dt = 0; //定义微分时间

    /*三个状态，先验状态，观测状态，最优估计状态*/
    float gyro_roll = 0, gyro_pitch = 0; //陀螺仪积分计算出的角度，先验状态
    float acc_roll = 0, acc_pitch = 0;   //加速度计观测出的角度，观测状态
    float k_roll = 0, k_pitch = 0;       //卡尔曼滤波后估计出最优角度，最优估计状态

    /*误差协方差矩阵P*/
    float e_P[2][2] = {{1, 0}, {0, 1}}; //误差协方差矩阵，这里的e_P既是先验估计的P，也是最后更新的P

    /*卡尔曼增益K*/
    float k_k[2][2] = {{0, 0}, {0, 0}}; //这里的卡尔曼增益矩阵K是一个2X2的方阵
    float Output[2];

public:
    // Kalman_filtering(MPU6050 mpu)
    // {
    //     mpu6050 = &mpu;
    // }
    /*初始化
     */
    void Filter_init(MPU6050 *mpu6050)
    {
        //计算偏移量
        for (i = 1; i <= 2000; i++)
        {
            mpu6050->update();
            // mpu.getEvent(&a, &g, &temp);//获取加速度、角速度、温度
            ax_offset = ax_offset + mpu6050->getAccX(); //计算x轴加速度的偏移总量
            ay_offset = ay_offset + mpu6050->getAccY(); //计算y轴加速度的偏移总量
            gx_offset = gx_offset + mpu6050->getGyroX();
            gy_offset = gy_offset + mpu6050->getGyroY();
        }
        ax_offset = ax_offset / 2000; //计算x轴加速度的偏移量
        ay_offset = ay_offset / 2000; //计算y轴加速度的偏移量
        gx_offset = gx_offset / 2000; //计算x轴角速度的偏移量
        gy_offset = gy_offset / 2000; //计算y轴角速度的偏移量
        delay(100);
    }

    /*
     * 卡尔曼滤波
     * Output[0]=k_roll;
     * Output[1]=k_pitch;
     */
    float *Filtering(MPU6050 *mpu6050)
    {
        /*计算微分时间*/
        now = millis();                 //当前时间(ms)
        dt = (now - lasttime) / 1000.0; //微分时间(s)
        lasttime = now;                 //上一次采样时间(ms)

        /*获取角速度和加速度 */
        mpu6050->update();

        /*step1:计算先验状态*/
        /*计算x,y轴上的角速度*/
        roll_v = (mpu6050->getGyroX() - gx_offset) + ((sin(k_pitch) * sin(k_roll)) / cos(k_pitch)) * (mpu6050->getGyroY() - gy_offset) + ((sin(k_pitch) * cos(k_roll)) / cos(k_pitch)) * mpu6050->getGyroZ(); // roll轴的角速度
        pitch_v = cos(k_roll) * (mpu6050->getGyroY() - gy_offset) - sin(k_roll) * mpu6050->getGyroZ();                                                                                                        // pitch轴的角速度
        gyro_roll = k_roll + dt * roll_v;                                                                                                                                                                     //先验roll角度
        gyro_pitch = k_pitch + dt * pitch_v;                                                                                                                                                                  //先验pitch角度

        /*step2:计算先验误差协方差矩阵P*/
        e_P[0][0] = e_P[0][0] + 0.0025; //这里的Q矩阵是一个对角阵且对角元均为0.0025
        e_P[0][1] = e_P[0][1] + 0;
        e_P[1][0] = e_P[1][0] + 0;
        e_P[1][1] = e_P[1][1] + 0.0025;

        /*step3:更新卡尔曼增益K*/
        k_k[0][0] = e_P[0][0] / (e_P[0][0] + 0.3);
        k_k[0][1] = 0;
        k_k[1][0] = 0;
        k_k[1][1] = e_P[1][1] / (e_P[1][1] + 0.3);

        /*step4:计算最优估计状态*/
        /*观测状态*/
        // roll角度
        acc_roll = atan((mpu6050->getAccY() - ay_offset) / (mpu6050->getAccZ())) * rad2deg;
        // pitch角度
        acc_pitch = -1 * atan((mpu6050->getAccX() - ax_offset) / sqrt(sq(mpu6050->getAccY() - ay_offset) + sq(mpu6050->getAccZ()))) * rad2deg;
        /*最优估计状态*/
        k_roll = gyro_roll + k_k[0][0] * (acc_roll - gyro_roll);
        k_pitch = gyro_pitch + k_k[1][1] * (acc_pitch - gyro_pitch);

        /*step5:更新协方差矩阵P*/
        e_P[0][0] = (1 - k_k[0][0]) * e_P[0][0];
        e_P[0][1] = 0;
        e_P[1][0] = 0;
        e_P[1][1] = (1 - k_k[1][1]) * e_P[1][1];

        //打印角度
        // Serial.print("roll:");
        // Serial.print(k_roll);
        // Serial.print(",");
        // Serial.print("pitch:");
        // Serial.println(k_pitch);
        Output[0] = k_roll;
        Output[1] = k_pitch;
        return Output;

        //姿态可视化
        //  Serial.print(k_roll);
        //  Serial.print("/");
        //  Serial.println(k_pitch);
    }
};