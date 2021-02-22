#include <WiFiManager.h>
#include <PubSubClient.h>
#include <WiFi.h>

class GestionConnexion
{
    public:
    void Initialiser();
    void Executer(String p_temperature,String p_pression, String p_humidite);
    private:

};