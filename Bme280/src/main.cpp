#include <Station.h>

Station station;

void setup()
{
  Serial.begin(115200);
  station.Initialiser();
}

void loop()
{
 station.Executer();
}