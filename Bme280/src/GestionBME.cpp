#include <GestionBME.h>


GestionBME::GestionBME(byte p_adresse): m_adresse(p_adresse)
{
 
}
void GestionBME::ValiderConnexion()
{
      if (!m_bme.begin(0x76)) {
		Serial.println("impossible de trouver le bme280, verifiez le branchement");
		while (1);
	}
    this->m_bme.begin(this->m_adresse);
}

String GestionBME::EnvoiTemperature()
{
  return String(this->m_bme.readTemperature());
}

String GestionBME::EnvoiPression()
{
  return String(this->m_bme.readPressure()/ 100.0F);
}

String GestionBME::EnvoilireHumidite()
{
 return String(this->m_bme.readHumidity());
}