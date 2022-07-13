#include <WebServer.h>
#include <LiquidCrystal.h>
#include "Si7034.h"
#include <LoRa.h>

//Capteur de température:
Si7034 si7034;

//-------------------Initialisation Serveur web-------------------
const char *ssid = "groupe8";
const char *password = "groupe8pswd";
WebServer server(80);

#define ss 18
#define rst 14
#define dio0 26
#define sck 5
#define miso 19
#define mosi 27



void handleRoot()
{
    String page = "<!DOCTYPE html>";
    page += "<head>";
    page += "    <title>Serveur de Tanguy et Thibault</title>";
    page += "    <meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'/>";
    page += "</head>";

    page += "<body lang='fr'>";
    page += "    <h1>Serveur Tanguy et Thibault</h1>";
    page += "    <p>Ce serveur est hébergé sur un ESP32</p>";
    page += "    <i>Créé par Tommy Desrochers</i>";
    page += "</body>";

    page += "</html>";

    server.send(200, "text/html", page);
}

void handleNotFound()
{
    server.send(404, "text/plain", "404: Not found");
}
//---------------------------------------------------------

//-------------------Paramètrage Ecran LCD-------------------
const int rs = 15, en = 2, d4 = 0, d5 = 4, d6 = 16, d7 = 17;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int index_col_lcd = 0;
//---------------------------------------------------------
void PrintLcdCapteurs(float humidity_out, float pressure,float temp_out, float temp_in, float humidity_in);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n");
    // set up the LCD's number of columns and rows:
    lcd.begin(20, 4);
    lcd.print("LCD OK");

    si7034.begin();
    if (si7034.queryDevice()) {
        Serial.println("SI7034: Capteur Opérationnel");
    }
    else {
        Serial.println("SI7034: ERROR, Capteur ne répond pas");
    }

    WiFi.persistent(false);
    WiFi.begin(ssid, password);
    Serial.print("Tentative de connexion...");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(100);
    }

    Serial.println("\n");
    Serial.println("Connexion etablie!");
    Serial.print("Adresse IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);
    server.begin();

    Serial.println("Serveur web actif!");

    Serial.println("LoRa Receiver");
    SPI.begin(sck, miso, mosi, ss);
    LoRa.setPins(18, 14, 26);    //setup LoRa transceiver module

    while (!LoRa.begin(866E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
    {
        Serial.println(".");
        delay(500);
    }
    LoRa.setSyncWord(0x01);
    Serial.println("LoRa Initializing OK!");

    lcd.clear();

}

void loop()
{

    Si7034_Result results_cap_serveur = si7034.fastMeasurement();
    float temp_out;
    float temp_in = results_cap_serveur.temperature;
    float humidity_out = 1;
    float humidity_in = results_cap_serveur.humidity;
    float pressure = 2;
    server.handleClient();
    PrintLcdCapteurs(humidity_out, pressure,temp_out, temp_in, humidity_in);

    int packetSize = LoRa.parsePacket();    // try to parse packet
    if (packetSize)
    {

        Serial.print("Received packet '");

        while (LoRa.available())              // read packet
        {
            String LoRaData = LoRa.readString();
            Serial.print(LoRaData);
        }
        Serial.print("' with RSSI ");         // print RSSI of packet
        Serial.println(LoRa.packetRssi());
    }


}


void PrintLcdCapteurs(float humidity_out, float pressure,float temp_out, float temp_in, float humidity_in) {
    //lcd.setCursor(n°colonne,n°ligne);
    lcd.setCursor(0,0);
    lcd.print("Interieur");
    lcd.setCursor(0,1);
    lcd.print("T-In : ");
    lcd.print(temp_in);
    lcd.print(" C");
    lcd.setCursor(0,2);
    lcd.print("H-In : ");
    lcd.print(humidity_in);
    lcd.print(" %");

    delay(4000);

    lcd.setCursor(0,0);
    lcd.print("Exterieur");
    lcd.setCursor(0,1);
    lcd.print("T-Out : ");
    lcd.print(temp_out);
    lcd.print(" C");

    lcd.setCursor(0,2);
    lcd.print("H-Out : ");
    lcd.print(humidity_out);
    lcd.print(" %");

    lcd.setCursor(0,3);
    lcd.print("P-Out : ");
    lcd.print(pressure);
    lcd.print(" bar");



    delay(4000);
    lcd.clear();
}
