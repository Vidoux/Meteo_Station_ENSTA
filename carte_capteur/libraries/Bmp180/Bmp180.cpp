#include "Arduino.h"
#include <Wire.h>

#include "Bmp180.h"

#define OUTPUT_MSB_ADDR  0xF6
#define Bmp180_ADDR      0x77
#define Bmp180_CTRL_ADDR 0xF4
#define PRESS_CMD_ADDR   0x34

Bmp180::Bmp180(){}

/*!
 * Récupérer la pression mesurée par le capteur
 * @return int32_t convertedPressure, Pression en Pascal (Pa)
 */
int32_t Bmp180::getPressure(){
    int32_t rawPressure = getRawPressure();
    int32_t convertedPressure = convertRawPressure(rawPressure);
    return convertedPressure;
}

/*!
 * Initialisation de la communication avec le capteur
 */
void Bmp180::begin(){
    Wire.begin();
    _ac1 = read2SignedByte(0xAA);
    _ac2 = read2SignedByte(0xAC);
    _ac3 = read2SignedByte(0xAE);
    _ac4 = read2UnsignedByte(0xB0);
    _ac5 = read2UnsignedByte(0xB2);
    _ac6 = read2UnsignedByte(0xB4);
    _b1 = read2SignedByte(0xB6);
    _b2 = read2SignedByte(0xB8);
    _mb = read2SignedByte(0xBA);
    _mc = read2SignedByte(0xBC);
    _md = read2SignedByte(0xBE);
    _oss = read2SignedByte(Bmp180_CTRL_ADDR);
    _oss = (_oss & 0xC0) >> 6;
}

/*!
 *
 * @return
 */
String Bmp180::toString(){
    return "Capteur BMP180\n"
                    "Depuis la bibliothèque de fonctionnalité conçue par Titi et Tang,\n"
                    "Fonctions disponibles: \n"
                    "       int32_t getPressure();\n"
                    "       void begin();\n"
                    "       void toString();";

}

/*!
 * Récupère la température "brut" (i.e. valuer non convertie en unitées "humaine")
 * @return int32_t pressure
 */
int32_t Bmp180::getRawPressure()
{
    uint8_t addr[2];
    addr[0] = Bmp180_CTRL_ADDR;
    addr[1] = PRESS_CMD_ADDR | (_oss << 6);
    Wire.beginTransmission(Bmp180_ADDR);
    Wire.write(addr, 2);
    Wire.endTransmission();

    switch (_oss){
        case 0:
            delay (4.5);
            break;
        case 1:
            delay (7.5);
            break;
        case 2:
            delay (13.5);
            break;
        case 3:
            delay (25.5);
            break;
        default:
            break;
    }

    Wire.beginTransmission(Bmp180_ADDR);
    Wire.write(OUTPUT_MSB_ADDR);
    Wire.endTransmission();
    Wire.requestFrom(Bmp180_ADDR, 2);

   if(Wire.available()){
        int8_t _msb = Wire.read();
        int8_t _lsb = Wire.read();
	    int32_t pressure = ((_msb <<  8) | (_lsb)) ;
        return pressure;
    }
    //Connexion au bus I2C impossible, retour erreur
    return -1;
}

/*!
 * Convertire une valeur de pression brute, du capteur, en valeur utilisable, en Bar.
 * @param int32_t raw_pressure
 * @return int32_t pressure, Pression en Pascal (Pa)
 */
int32_t Bmp180::convertRawPressure(int32_t raw_pressure){
    int32_t pressure;

    _b6 = _b5 - 4000;
    _x1 = (_b2 * (_b6 * _b6 / pow(2, 12))) / pow(2, 11);
    _x2 = _ac2 * _b6 / pow(2, 11);
    _x3 = _x1 + _x2;
    _b3 = ((_ac1 * 4 + _x3) << _oss + 2) / 4;
    _x1 = _ac3 * _b6 / pow(2, 13);
    _x2 = (_b1 * (_b6 * _b6 / pow(2, 12))) / pow(2, 16);
    _x3 = ((_x1 + _x2) + 2) / pow(2, 2);
    _b4 = _ac4 * (uint64_t)(_x3 + 32768) / pow(2, 15);
    _b7 = ((uint64_t)raw_pressure - _b3) * (50000 >> _oss);
    if (_b7 < 0x80000000){
        pressure = (_b7 * 2) / _b4;
    }
    else{
        pressure = (_b7 / _b4) *2;
    }
    _x1 = (pressure / pow(2, 8)) * (pressure / pow(2, 8));
    _x1 = (_x1 * 3038) / pow(2, 16);
    _x2 = (-7357 * pressure) / pow(2, 16);
    pressure = pressure + (_x1 + _x2 + 3791) / pow(2, 4);

    return pressure;
}

/*!
 * Lire 2 Octets signés à l'adresse donnée
 * @param int8_t address
 * @return int32_t res,
 */
int32_t Bmp180::read2SignedByte(int8_t address){

    Wire.beginTransmission(Bmp180_ADDR);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(Bmp180_ADDR, 2);


    if (2 <= Wire.available()){
        int8_t _msb = Wire.read();
        int8_t _lsb = Wire.read();
        
        int32_t res = (_msb << 8) | _lsb;

        return res;
    }
    return -1;
}

/*!
 * Lire 2 Octets non-signés à l'adresse donnée
 * @param int8_t address
 * @return int32_t res,
 */
uint32_t Bmp180::read2UnsignedByte(int8_t address){

    Wire.beginTransmission(Bmp180_ADDR);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(Bmp180_ADDR, 2);

    if (2 <= Wire.available()){
        uint8_t _msb = Wire.read();
        uint8_t _lsb = Wire.read();
        
        uint32_t res = (_msb << 8) | _lsb;

        return res;
    }
    return -1;
}
