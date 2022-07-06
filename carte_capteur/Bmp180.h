//
// Created by Tanguy on 06/07/2022.
//
#include "Arduino.h"

#ifndef Bmp180

#define Bmp180

#define Bmp180_ADDR 0x77
#define Bmp180_CTRL_ADDR 0xf4

#define PRESS_CMD_ADDR 0x34

#define OUTPUT_MSB_ADDR  0xf6
#define OUTPUT_XLSB_ADDR 0xf8

#define ac1_MSB 0xaa
#define ac2_MSB 0xac
#define ac3_MSB 0xae
#define ac4_MSB 0xb0
#define ac5_MSB 0xb2
#define ac6_MSB 0xb4
#define b1_MSB  0xb6
#define b2_MSB  0xb8
#define mb_MSB  0xba
#define mc_MSB  0xbc
#define md_MSB  0xbe

class Bmp180{

public:
    Bmp180();

    int32_t readPressure(void);
    void begin();

private:
    int32_t readPressure();
    int32_t convertRawPressure(int32_t rawPressure);
    int32_t read2SignedByte(int8_t addr);
    uint32_t read2UnsignedByte(int8_t addr);

    int16_t _ac1, _ac2, _ac3, _b1, _b2, _mb, _mc, _md, _oss;
    uint16_t _ac4, _ac5, _ac6;
    int32_t _x1, _x2, _x3, _b3, _b5, _b6, _b7 ;
    uint32_t _b4;

};

#endif




