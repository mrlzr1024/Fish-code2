#ifndef  __UART_H__
#define __UART_H__
#include<reg52.h>
extern 	void Uart_init(void);//初始化串口
extern int BluetoothGet(void);
extern int BluetoothGetOnce(void);//获取一次
extern void Uart() ;

#endif