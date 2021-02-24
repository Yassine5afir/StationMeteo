#include <GestionConnexion.h>


WiFiClient espClient;
PubSubClient client(espClient);

// WI-FI
const char *ssid = "Bleu";
const char *password = "Bleu1234";

// MQTT
char mqtt_Server[15];
char mqtt_Port[5];
char mqtt_User[40];
char mqtt_Password[100];
const char *mqttServer = "192.168.2.23";
const char *mqttPort = "1883";
const char *mqttUser = "homeassistant";
const char *mqttPassword = "ovaeD9aikeegh1oozeeTh6ongay4aechung3naeyeid8Ephei7Ro6uo4nais8Xap";

bool shouldSaveConfig = false; //metttre m_

WiFiManager wm;

void Callback()
{
    Serial.println("Should save config");
    shouldSaveConfig = true;
}

void GestionConnexion::SauvegardeDonneesSpiffs()
{
    if (shouldSaveConfig)
    {
        File fichierJson = SPIFFS.open("/configuration.json", "r");

        DynamicJsonDocument doc(512);

        deserializeJson(doc, fichierJson);

        doc["mqtt server"] = mqtt_Server;
        doc["mqtt Port"] = mqtt_Port;
        doc["mqtt user"] = mqtt_User;
        doc["mqtt password"] = mqtt_Password;

        serializeJson(doc, fichierJson);

        fichierJson.close();

        doc.clear();

        shouldSaveConfig = false;

        Serial.println("Configuration SPIFFS avec succès ...");
    }

    else
    {
        Serial.println("Les configurations ne sont pas enregistrées");
    }
    
}

void GestionConnexion::Initialiser()
{
    WiFi.mode(WIFI_STA);
    wm.setSaveConfigCallback(Callback);
    WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqttServer, 15);
    WiFiManagerParameter custom_mqtt_port("port", "mqtt Port", mqttPort, 5);
    WiFiManagerParameter custom_mqtt_user("user", "mqtt user", mqttUser, 40);
    WiFiManagerParameter custom_mqtt_password("password", "mqtt password", mqttPassword, 100);

    wm.addParameter(&custom_mqtt_server);
    wm.addParameter(&custom_mqtt_port);
    wm.addParameter(&custom_mqtt_user);
    wm.addParameter(&custom_mqtt_password);

    // partir la connexion wi-fi
    if (!wm.autoConnect(ssid, password))
    {
        Serial.println("erreur de connection");
    }
    else
    {
        Serial.println("Connexion etablie");
        Callback();
    }

    strcpy(mqtt_Server, custom_mqtt_server.getValue());
    strcpy(mqtt_Port, custom_mqtt_port.getValue());
    strcpy(mqtt_User, custom_mqtt_user.getValue());
    strcpy(mqtt_Password, custom_mqtt_password.getValue());

    client.setServer(mqtt_Server, atoi(mqtt_Port));

    while (!client.connected())
    {
        Serial.println("Connexion à MQTT...");

        if (client.connect("ESP32Client", mqtt_User, mqtt_Password))
        {

            Serial.println("connecte");
        }
        else
        {

            Serial.print("erreur num : ");
            Serial.print(client.state());
            wm.startConfigPortal(ssid, password);
            strcpy(mqtt_Server, custom_mqtt_server.getValue());
            strcpy(mqtt_Port, custom_mqtt_port.getValue());
            strcpy(mqtt_User, custom_mqtt_user.getValue());
            strcpy(mqtt_Password, custom_mqtt_password.getValue());
            delay(2000);
        }
    }
}

void GestionConnexion::Executer(String p_temperature, String p_pression, String p_humidite)
{
    client.publish("esp32/BME2800/temperature", p_temperature.c_str());
    client.publish("esp32/BME2800/humidity", p_pression.c_str());
    client.publish("esp32/BME2800/pressure", p_humidite.c_str());
    client.loop();
}