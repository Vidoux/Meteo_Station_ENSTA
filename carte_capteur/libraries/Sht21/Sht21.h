//
// Created by Tanguy on 10/07/2022.
//
#include <Arduino.h>

#ifndef METEO_STATION_ENSTA_Sht21_H
#define METEO_STATION_ENSTA_Sht21_H

class Sht21
{
public:
    Sht21();

    void begin();
    float getTemperature();
    float getHumidity();

private:
    uint16_t getRawTemperature();
    uint16_t getRawHumidity();
    float convertRawTemperature(uint16_t rawTemperature);
    float convertRawHumidity(uint16_t rawHumidity);
};

#endif