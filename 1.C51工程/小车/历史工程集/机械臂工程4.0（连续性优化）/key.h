/*
 * @Author: your name
 * @Date: 2021-11-17 07:46:47
 * @LastEditTime: 2021-11-21 07:33:44
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \机械臂\key.h
 */
#ifndef __KEY_H__
#define __KEY_H__
#include<REG52.h>
#define KEY P1
sbit key0 = P0 ^ 0;
sbit key1 = P0 ^ 1;

extern int key(void);
extern int key_continue(void);
extern int key4x4(void);


#endif // !__KEY_H__
