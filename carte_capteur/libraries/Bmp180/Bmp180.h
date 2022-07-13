#include "Arduino.h"

#ifndef METEO_STATION_ENSTA_Bmp180_H
#define METEO_STATION_ENSTA_Bmp180_H

class Bmp180{

    public:

        Bmp180();
        int32_t getPressure();
        void begin();
        String toString();

    private:

        int32_t getRawPressure();
        int32_t convertRawPressure(int32_t rawPressure);
        int32_t read2SignedByte(int8_t address);
        uint32_t read2UnsignedByte(int8_t address);
        
        int16_t _ac1, _ac2, _ac3, _b1, _b2, _mb, _mc, _md, _oss;
        uint16_t _ac4, _ac5, _ac6;
        int32_t _x1, _x2, _x3, _b3, _b5, _b6, _b7 ;
        uint32_t _b4;
};

#endif