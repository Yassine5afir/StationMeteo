#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

#include <AffichageLCD.h>

#define SEALEVELPRESSURE_HPA (1013.25)


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
AffichageLCD affichage;

void setup()
{
  // initialiser le LCD
  affichage.Initialiser();

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

  affichage.Afficher(String(bme.readTemperature()),String(bme.readHumidity()),String(bme.readPressure() / 100.0F));

  client.publish("esp32/BME2800/temperature", temperature.c_str());
  client.publish("esp32/BME2800/humidity", humidite.c_str());
  client.publish("esp32/BME2800/pressure", pression.c_str());
  client.loop();



	Serial.println(bme.readTemperature());
	Serial.println(bme.readPressure() / 100.0F);
	Serial.println(bme.readHumidity());
	Serial.println();
  delay(500);
}
