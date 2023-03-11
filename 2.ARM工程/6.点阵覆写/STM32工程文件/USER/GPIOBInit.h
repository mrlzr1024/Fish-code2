/*
 * @Author: your name
 * @Date: 2021-12-05 17:13:58
 * @LastEditTime: 2021-12-05 17:21:25
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \USER\GPIOBInit.h
 */
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
