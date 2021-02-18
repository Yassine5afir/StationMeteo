#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define lcdColonnes 16
#define lcdRangees 2


LiquidCrystal_I2C lcd(0x27, lcdColonnes, lcdRangees);  

// WI-FI
const char *ssid = "BELL619";
const char *password = "A4765714AA4D";

// MQTT
const char *mqttServer = "192.168.2.23";
const int mqttPort = 1883;
const char *mqttUser = "homeassistant";
const char *mqttPassword = "ovaeD9aikeegh1oozeeTh6ongay4aechung3naeyeid8Ephei7Ro6uo4nais8Xap";

// OBJETS
Adafruit_BME280 bme;
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  // initialiser le LCD
  lcd.init();
  lcd.backlight();

  // Verifie si le BME est bien trouvé
  if (!bme.begin(0x76)) {
		Serial.println("impossible de trouver le bme280, verifiez le branchement");
		while (1);
	}

  Serial.begin(115200);

  // partir la connexion wi-fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connexion au WiFi..");
  }

  Serial.println("Connecte au reseau Wifi");


  // configurer mqtt serveur
  client.setServer(mqttServer, mqttPort);

  while (!client.connected())
  {
    Serial.println("Connexion à MQTT...");

    if (client.connect("ESP32Client", mqttUser, mqttPassword))
    {

      Serial.println("connecte");
    }
    else
    {

      Serial.print("erreur num : ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop()
{
 
  String temperature = String(bme.readTemperature());
  String humidite = String(bme.readHumidity());
  String pression = String(bme.readPressure() / 100.0F);

  client.publish("esp32/BME2800/temperature", temperature.c_str());
  client.publish("esp32/BME2800/humidity", humidite.c_str());
  client.publish("esp32/BME2800/pressure", pression.c_str());
  client.loop();

  String listeInformation[3] = {temperature, humidite, pression} ;
  String listeCleInformation[3] = {"temp", "hum", "pres"};
  String UnitesInformations[3] = {"C", "g/m3", "kpa" };
  String BonneJournee = "bonne journee :)";
  String Decor = "--*-- :-) --*--";

  for (int nbrElements = 0; nbrElements < 4; ++nbrElements)
  {
    if (nbrElements < 3)
    {
      lcd.setCursor(1, 0);
      lcd.print(listeCleInformation[nbrElements] + ": " + listeInformation[nbrElements] + " " + UnitesInformations[nbrElements]);
      lcd.setCursor(0, 1);
      lcd.print(Decor);
      delay(2000);
      lcd.clear();
  
      lcd.setCursor(0,1);
      lcd.print(listeCleInformation[nbrElements] + ": " + listeInformation[nbrElements] + " " + UnitesInformations[nbrElements]);
      lcd.setCursor(1, 0);
      lcd.print(Decor);
      delay(2000);
      lcd.clear();
    }
 
    else if (nbrElements == 3)
    {
      lcd.setCursor(0,1);
      lcd.print(BonneJournee);
      delay(2000);
      lcd.clear();

      nbrElements = -1;
    }
  }

	Serial.println(bme.readTemperature());
	Serial.println(bme.readPressure() / 100.0F);
	Serial.println(bme.readHumidity());
	Serial.println();
  delay(500);
}
