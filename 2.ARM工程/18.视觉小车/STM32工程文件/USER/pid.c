/*
 * @Descripttion: Project's name
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-15 15:50:55
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-26 22:13:59
 */
#include "pid.h"
// 1.增量式pid
//定义PID相关宏
//  这三个参数设定对电机运行影响非常大
/*************************************/
float Proportion =0.3; //比例常数 Proportional Const
//P产生响应速度和力度，过小响应慢，过大会产生振荡，是I和D的基础。
float Integral =0.1;//1.5; //积分常数 Integral Const
//I在有系统误差和外力作用时消除偏差、提高精度，同时也会增加响应速度，产生过冲，过大会产生振荡。
float Derivative = 0.1; //微分常数 Derivative Const
//D抑制过冲和振荡，过小系统会过冲，过大会减慢响应速度。D的另外一个作用是抵抗外界的突发干扰，阻止系统的突变。




float P_r = 0.2; //比例常数 Proportional Const
float I_r = 0.1; //积分常数 Integral Const
float D_r = 0.4; //微分常数 Derivative Const

/********************增量式PID控制设计************************************/
// NextPoint当前输出值
// SetPoint设定值

//左轮PID
int PID_Calc_Left(int NextPoint, int SetPoint)
{

  static int LastError; // Error[-1]
  static int PrevError; // Error[-2]
  int iError, Outpid;   //当前误差

  iError = SetPoint - NextPoint;       //增量计算
  Outpid = (Proportion * iError)       // E[k]项
           - (Integral * LastError)    // E[k-1]项
           + (Derivative * PrevError); // E[k-2]项

  PrevError = LastError; //存储误差，用于下次计算
  LastError = iError;
  return (Outpid); //返回增量值
}

//右轮PID
int PID_Calc_Right(int NextPoint, int SetPoint)
{
  static int LastError_r; // Error[-1]
  static int PrevError_r; // Error[-2]
  int iError_r, Outpid_r;   //当前误差

  iError_r = SetPoint - NextPoint;       //增量计算
  Outpid_r = (P_r * iError_r)       // E[k]项
           - (I_r * LastError_r)    // E[k-1]项
           + (D_r * PrevError_r); // E[k-2]项

  PrevError_r = LastError_r; //存储误差，用于下次计算
  LastError_r = iError_r;
  return (Outpid_r); //返回增量值
}
