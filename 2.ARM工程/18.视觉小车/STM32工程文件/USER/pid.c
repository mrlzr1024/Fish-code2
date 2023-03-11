/*
 * @Descripttion: Project's name
 * @version: 1.0
 * @Author: MrLZR
 * @Date: 2022-06-15 15:50:55
 * @LastEditors: MrLZR
 * @LastEditTime: 2022-06-26 22:13:59
 */
#include "pid.h"
// 1.����ʽpid
//����PID��غ�
//  �����������趨�Ե������Ӱ��ǳ���
/*************************************/
float Proportion =0.3; //�������� Proportional Const
//P������Ӧ�ٶȺ����ȣ���С��Ӧ�������������񵴣���I��D�Ļ�����
float Integral =0.1;//1.5; //���ֳ��� Integral Const
//I����ϵͳ������������ʱ����ƫ���߾��ȣ�ͬʱҲ��������Ӧ�ٶȣ��������壬���������񵴡�
float Derivative = 0.1; //΢�ֳ��� Derivative Const
//D���ƹ�����񵴣���Сϵͳ����壬����������Ӧ�ٶȡ�D������һ�������ǵֿ�����ͻ�����ţ���ֹϵͳ��ͻ�䡣




float P_r = 0.2; //�������� Proportional Const
float I_r = 0.1; //���ֳ��� Integral Const
float D_r = 0.4; //΢�ֳ��� Derivative Const

/********************����ʽPID�������************************************/
// NextPoint��ǰ���ֵ
// SetPoint�趨ֵ

//����PID
int PID_Calc_Left(int NextPoint, int SetPoint)
{

  static int LastError; // Error[-1]
  static int PrevError; // Error[-2]
  int iError, Outpid;   //��ǰ���

  iError = SetPoint - NextPoint;       //��������
  Outpid = (Proportion * iError)       // E[k]��
           - (Integral * LastError)    // E[k-1]��
           + (Derivative * PrevError); // E[k-2]��

  PrevError = LastError; //�洢�������´μ���
  LastError = iError;
  return (Outpid); //��������ֵ
}

//����PID
int PID_Calc_Right(int NextPoint, int SetPoint)
{
  static int LastError_r; // Error[-1]
  static int PrevError_r; // Error[-2]
  int iError_r, Outpid_r;   //��ǰ���

  iError_r = SetPoint - NextPoint;       //��������
  Outpid_r = (P_r * iError_r)       // E[k]��
           - (I_r * LastError_r)    // E[k-1]��
           + (D_r * PrevError_r); // E[k-2]��

  PrevError_r = LastError_r; //�洢�������´μ���
  LastError_r = iError_r;
  return (Outpid_r); //��������ֵ
}
