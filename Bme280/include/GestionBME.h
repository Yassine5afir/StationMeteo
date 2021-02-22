#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Arduino.h>

class GestionBME
{
private:
    Adafruit_BME280 m_bme;
    byte m_adresse;
public:
    GestionBME(byte p_adresse);
    void ValiderConnexion();
    String EnvoiTemperature();
    String EnvoiPression();
    String EnvoilireHumidite();
   
};


