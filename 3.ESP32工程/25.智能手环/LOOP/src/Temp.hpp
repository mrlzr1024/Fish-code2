#ifndef __TEMP_H
#define __TEMP_H

#include <OneWire.h>
#include <DS18B20.h>

#define ONE_WIRE_BUS 13

extern float Temperature;
extern void Temp_init();
extern float Temp_read();

#endif