#include <AffichageLCD.h>

static const int lcdRangees = 2;
static const int lcdColonnes = 16;
LiquidCrystal_I2C lcd(0x27, lcdColonnes, lcdRangees);

AffichageLCD::AffichageLCD()
{
}

void AffichageLCD::Afficher(String p_temp, String p_pression, String p_humidite)
{
    m_temperature = p_temp;
    m_pression = p_pression;
    m_humidite = p_humidite;

    String listeInformation[3] = {m_temperature, m_humidite, m_pression};
    String listeCleInformation[3] = {"temp", "hum", "pres"};
    String UnitesInformations[3] = {"C", "g/m3", "kpa"};
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

}

void AffichageLCD::Initialiser()
{
    lcd.init();
    lcd.backlight();
}