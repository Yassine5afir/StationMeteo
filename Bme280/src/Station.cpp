#include <Station.h>

#define adresse 0x76

AffichageLCD affichage;
GestionBME gestionBME = GestionBME(adresse);
GestionConnexion connexionWifi;

void Station::Initialiser()
{
    connexionWifi.Initialiser();
    connexionWifi.SauvegardeDonneesSpiffs();
    affichage.Initialiser();
    gestionBME.ValiderConnexion();
}

void Station::Executer()
{
    String temperature = gestionBME.EnvoiTemperature();
    String humidite = gestionBME.EnvoilireHumidite();
    String pression = gestionBME.EnvoiPression();
    
    connexionWifi.Executer(temperature,pression,humidite);
    affichage.Afficher(temperature, humidite, pression);
}