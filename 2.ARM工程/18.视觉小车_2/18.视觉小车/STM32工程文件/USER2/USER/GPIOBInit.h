/*
 *名称：GPIOBInit(gpioboxInit)
 *用途：初始化管脚
 */
#ifndef __GPIOBINIT_H
#define __GPIOBINIT_H
#include "stm32f10x.h"
/*
 *函数名称：InitGPIO
 *输入：int pin//哪一号管脚,
        int frequency//频率,
        GPIO_TypeDef *GPIOX//哪一组管脚
 *输出：无
 *备注：默认以推挽方式输出
*/
extern void InitGPIO(int pin,int frequency,GPIO_TypeDef *GPIOX);

#endif // !
