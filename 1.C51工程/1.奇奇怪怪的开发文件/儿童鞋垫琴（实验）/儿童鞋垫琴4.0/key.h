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
