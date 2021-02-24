#include <FS.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

class GestionConnexion
{
    public:
    void Initialiser();
    void SauvegardeDonneesSpiffs();
    void Executer(String p_temperature,String p_pression, String p_humidite);
    private:

};