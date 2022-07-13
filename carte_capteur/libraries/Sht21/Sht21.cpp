//
// Created by Tanguy on 10/07/2022.
//

#include <Arduino.h>
#include <Wire.h>

#include "Sht21.h"

#define Sht21_ADDR    0x40

#define TEMP_CMD_NO_HOLD_ADDR 0xF3
#define RH_CMD_NO_HOLD_ADDR   0xF5


Sht21::Sht21(){
}

void Sht21::begin(){
    Wire.begin();
}

float Sht21::getTemperature(){
    uint16_t rawTemperature = getRawTemperature();
    float convertedTemperature = convertRawTemperature(rawTemperature);

    return convertedTemperature;
}

float Sht21::getHumidity(){
    uint16_t rawHumidity = getRawHumidity();
    float convertedHumidity = convertRawHumidity(rawHumidity);

    return convertedHumidity;
}

uint16_t Sht21::getRawTemperature(){
    Wire.beginTransmission(Sht21_ADDR);
    Wire.write(TEMP_CMD_NO_HOLD_ADDR);
    Wire.endTransmission();

    delay(150);

    Wire.requestFrom(Sht21_ADDR, 3);

    if (3 <= Wire.available()){
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();
        //TODO ajouter la vérification de la checksum
        uint16_t _rawTemperature = _msb << 8 | _lsb;

        return _rawTemperature;
    }

    return -1;
}

uint16_t Sht21::getRawHumidity(){
    Wire.beginTransmission(Sht21_ADDR);
    Wire.write(RH_CMD_NO_HOLD_ADDR);
    Wire.endTransmission();

    delay(150);

    Wire.requestFrom(Sht21_ADDR, 3);

    while (3 <= Wire.available()){
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();
        //TODO ajouter la vérification de la checksum
        uint16_t _rawHumidity = _msb << 8 | _lsb;
        return _rawHumidity;
    }
    return -1;
}

float Sht21::convertRawTemperature(uint16_t rawTemperature){
    float temperature = -46.85 + 175.72*((float)rawTemperature / (pow(2, 16)));
    return temperature;
}

float Sht21::convertRawHumidity(uint16_t rawHumidity){
    float humidity = -6 + 125*((float)rawHumidity / (pow(2, 16)));
    return humidity;
}


