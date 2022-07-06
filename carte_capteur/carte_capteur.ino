
#include <LiquidCrystal.h>
const int d4=4,d5=5,d6=6,d7=7,en=3,rs=2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
    lcd.clear();
    pinMode(14, OUTPUT);
    Serial.begin(115200);
    Serial.println("bonjour");
    lcd.begin(8,2);
}

// the loop function runs over and over again forever
void loop() {
    PrintLcdCapteurs(3.3,78,150,19);
    // wait for a second
}


void PrintLcdCapteurs(float batterie, float humidity_out, float pressure, float tempout) {
    digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
    lcd.setCursor(0,0);
    lcd.print("Voltage:");
    lcd.setCursor(0,1);
    lcd.print(batterie);
    lcd.print("V");

    delay(2000);
    lcd.clear();
    delay(100);
    digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
    delay(100);

    lcd.setCursor(0,0);
    lcd.print("Humid:");
    lcd.setCursor(0,1);
    lcd.print(humidity_out);
    lcd.print("%");

    delay(2000);
    lcd.clear();
    delay(100);
    digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
    delay(100);

    lcd.setCursor(0,0);
    lcd.print("Pression:");
    lcd.setCursor(0,1);
    lcd.print(pressure);
    lcd.print("B");

    delay(2000);
    lcd.clear();
    delay(100);
    digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
    delay(100);

    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.setCursor(0,1);
    lcd.print(tempout);
    lcd.print("C");

    delay(2000);
    lcd.clear();
    delay(100);
    digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);                       // wait for a second
    digitalWrite(14, LOW);    // turn the LED off by making the voltage LOW
    delay(100);
}
