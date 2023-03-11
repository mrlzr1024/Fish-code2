// //
// //    FILE: DS18B20_test.ino
// //  AUTHOR: Rob Tillaart
// // PURPOSE: Minimal DS18B20 lib with async support.
// //     URL: https://github.com/RobTillaart/DS18B20_RT

#include "Temp.hpp"
OneWire oneWire(ONE_WIRE_BUS);
DS18B20 sensor(&oneWire);
float Temperature;
void Temp_init()
{
    sensor.begin();
    sensor.setResolution(12);
    sensor.requestTemperatures();
}

float Temp_read()
{

    sensor.setResolution(12);
    sensor.requestTemperatures();
    // while (!sensor.isConversionComplete())
    //     ;
    sensor.isConversionComplete();
    Temperature = sensor.getTempC();
    return Temperature;
    // Serial.println(t, 1);
}
