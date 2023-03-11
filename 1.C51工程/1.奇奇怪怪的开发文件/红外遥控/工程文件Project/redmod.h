/*
 * @Author: your name
 * @Date: 2021-12-10 07:58:18
 * @LastEditTime: 2021-12-10 08:17:23
 * @LastEditors: your name
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \工程文件Project\redmod.h
 */
#ifndef __REDMOD_H
#define __REDMOD_H
#include <reg52.h>
sbit IRIN = P3 ^ 2;
typedef unsigned int u16; //对数据类型进行声明定义
typedef unsigned char u8;
extern void ReadIr();//利用外部中断0
extern void IrInit();//红外线初始化
extern u8 IrValue[6];//[0]=地址码；[1]=地址反码；[2]=控制码；[3]=控制反码

#endif