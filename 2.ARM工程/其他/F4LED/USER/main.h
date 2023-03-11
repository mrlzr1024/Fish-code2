#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f4xx.h"
void Error_Handler(void);
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define ZK_CS_Pin GPIO_PIN_2
#define ZK_CS_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_10
#define OLED_DC_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_12
#define OLED_CS_GPIO_Port GPIOB
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned int
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
