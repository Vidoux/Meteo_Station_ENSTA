#include <WebServer.h>
#include <LiquidCrystal.h>


//-------------------Initialisation Serveur web-------------------
const char *ssid = "groupe8";
const char *password = "groupe8pswd";
WebServer server(80);

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
void PrintLcdCapteurs(float humidity_out, float pressure, float temp, float humidity_in);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n");
    // set up the LCD's number of columns and rows:
    lcd.begin(20, 4);
    lcd.print("LCD OK");

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
    lcd.clear();

}

void loop()
{
    float temp = 35.0;
    float humidity_out = 1;
    float humidity_in = 2;
    float pressure = 2;
    server.handleClient();
    PrintLcdCapteurs(humidity_out, pressure, temp, humidity_in);


}


void PrintLcdCapteurs(float humidity_out, float pressure, float temp, float humidity_in) {
    //lcd.setCursor(n°colonne,n°ligne);
    lcd.setCursor(0,0);
    lcd.println("Interieur");
    lcd.setCursor(0,1);
    lcd.print("T-In : ");
    lcd.print(temp);
    lcd.println(" C");
    lcd.setCursor(0,2);
    lcd.print("H-In : ");
    lcd.print(humidity_in);
    lcd.println(" %");

    delay(4000);

    lcd.setCursor(0,0);
    lcd.println("Exterieur");
    lcd.setCursor(0,1);
    lcd.print("T-Out : ");
    lcd.print(temp);
    lcd.println(" C");

    lcd.setCursor(0,2);
    lcd.print("H-Out : ");
    lcd.print(humidity_out);
    lcd.println(" %");

    lcd.setCursor(0,3);
    lcd.print("P-Out : ");
    lcd.print(pressure);
    lcd.println(" bar");



    delay(4000);
    lcd.clear();
}
