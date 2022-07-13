//
// Created by Tanguy on 12/07/2022.
//
#include <Arduino.h>
#include <Wire.h>
#include "Si7034.h"



void Si7034::begin(){
    _address = 0x70;
    Wire.begin();
}

Si7034_Result Si7034::normalMeasurement() {
    return noHoldModeMeasurement(0x7866);
}

Si7034_Result Si7034::fastMeasurement() {
    return noHoldModeMeasurement(0x609C);
}

Si7034_Result Si7034::noHoldModeMeasurement(uint16_t hexCode) {

    Si7034_Result results;
    results.error = 0xFF;

    Wire.beginTransmission(_address);
    Wire.write(0x78);
    Wire.endTransmission();

    delay(70);

    Wire.requestFrom(_address, 2);
    if (2 <= Wire.available())
    {
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();
        results.temperature = _msb << 8 | _lsb;
    }
    else {
        results.error = 0x11;
    }
    //récupération humidité
    Wire.beginTransmission(_address);
    Wire.write(0x66);
    Wire.endTransmission();
    delay(70);

    Wire.requestFrom(_address, 2);

    if (2 <= Wire.available())
    {
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();

         ((_msb << 8) | (_lsb));
    }


    return results;
}

float Si7034::calculateT(uint16_t rawValue) {
    return -45 + 175 * (rawValue / pow(2,16));
}

float Si7034::calculateRH(uint16_t rawValue) {
    return 100 * (rawValue / pow(2, 16));
}

bool Si7034::queryDevice()
{
    bool result = false;

    Wire.beginTransmission(_address);
    Wire.write(0xEF);
    Wire.write(0xC8);
    Wire.endTransmission();

    delay(25);

    uint8_t	buf[3];
    Wire.requestFrom(_address, (uint8_t)3);

    if (Wire.readBytes(buf, (int8_t)3) == 3) {
        if (buf[0] == 0x00 && buf[1] == 0x47 && buf[2] == 0x2B) {
            result = true;
        }
    }
    return result;
}
