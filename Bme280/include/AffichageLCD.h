#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class AffichageLCD
{

public:
    AffichageLCD();
    void Initialiser();
    void Afficher(String p_temp, String p_pression, String p_humidite);
private:
    String m_temperature;
    String m_pression;
    String m_humidite;
};