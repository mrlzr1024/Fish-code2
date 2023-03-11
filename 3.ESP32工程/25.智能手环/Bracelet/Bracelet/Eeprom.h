#ifndef __EEPROM_H
#define __EEPROM_H

#include <Wire.h> // 使用Wire库，需要包含头文件
#include "main.h"
extern uint8_t at24c02_write(char data_wr, uint8_t WriteAddr);
extern uint8_t at24c02_read(char *data_wr, uint8_t ReadAddr);
extern void RTC_Init();

#endif