//
// Created by Tanguy on 12/07/2022.
//
#include <Arduino.h>

#ifndef METEO_STATION_ENSTA_SI7034_H
#define METEO_STATION_ENSTA_SI7034_H


struct Si7034_Result {
    float temperature;
    float humidity;
    uint8_t error;
};


class Si7034 {

    public:
        void begin();
        uint16_t readFirmwareRevision(); // 0x10 = Firware version 1.0
        Si7034_Result normalMeasurement();
        Si7034_Result fastMeasurement();
        bool queryDevice();

    private:
        uint8_t _address;

        Si7034_Result noHoldModeMeasurement(uint16_t hexCode);
        float calculateT(uint16_t rawValue);
        float calculateRH(uint16_t rawValue);

};


#endif //METEO_STATION_ENSTA_SI7034_H
