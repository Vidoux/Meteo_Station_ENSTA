#include <LiquidCrystal.h>
#include <Wire.h>
#include <Bmp180.h>
#include <Sht21.h>

const int d4=4,d5=5,d6=6,d7=7,en=3,rs=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
const int LED = 14;

Bmp180 bmp;
Sht21 sht;

void PrintLcdCapteurs(float batterie, float humidity_out, float pressure, float tempout);
void ledBlink(int delay_val);

void setup() {
    Serial.begin(19200);
    bmp.begin();
    lcd.begin(8,2);
    pinMode(LED, OUTPUT);

    Serial.println(bmp.toString());
    lcd.print("LCD OK");
}


void loop() {
    lcd.clear();

    long pressure_pa = bmp.getPressure();
    float pressure_bar = float(pressure_pa) / 100000;
    Serial.println(pressure_bar);
    float humidity_out = sht.getHumidity();
    float temp_out = sht.getTemperature();


    PrintLcdCapteurs(3.3,humidity_out,pressure_bar,temp_out);
}


void PrintLcdCapteurs(float batterie, float humidity_out, float pressure, float temp_out) {
    ledBlink(300);
    lcd.setCursor(0,0);
    lcd.print("Voltage:");
    lcd.setCursor(0,1);
    lcd.print(batterie);
    lcd.print("V");

    delay(2000);
    lcd.clear();
    ledBlink(300);

    lcd.setCursor(0,0);
    lcd.print("Humid:");
    lcd.setCursor(0,1);
    lcd.print(humidity_out);
    lcd.print("%");

    delay(2000);
    lcd.clear();
    ledBlink(300);

    lcd.setCursor(0,0);
    lcd.print("Pression:");
    lcd.setCursor(0,1);
    lcd.print(pressure);
    lcd.setCursor(5,1);
    lcd.print("Bar");

    delay(2000);
    lcd.clear();
    ledBlink(300);

    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print(temp_out);
    lcd.print("C");

    delay(2000);
    lcd.clear();
    ledBlink(300);
}

void ledBlink(int delay_val){
    digitalWrite(LED, HIGH);
    delay(delay_val);
    digitalWrite(LED, LOW);
    delay(delay_val);
}
