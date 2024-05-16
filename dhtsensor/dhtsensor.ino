

#include "DHT.h"             // Bibliotheek voor DHT sensoren

#define sensorpin 2            // data pin


//Welke DHT chip 
#define dhtType DHT11        // DHT 11


DHT dht(sensorpin, dhtType);    // Initialiseer de DHT bibliotheek

float tempC;              // temperatuur in graden Celcius

void setup() 
{
  Serial.begin(9600);        // stel de seriële monitor in
  dht.begin();               // start het DHT sensor uitlezen
}

void loop() {
  
  delay(1000);

  tempC = dht.readTemperature();   //vraag temperatuur     

  // Controleer of alle waarden goed zijn uitgelezen, zo niet probeer het opnieuw
  if (isnan(tempC)) {
    Serial.println("Uitlezen van DHT sensor mislukt!");
    
    return;
  }
  

  // seriële monitor

  Serial.print("Temperatuur: ");
  Serial.print(tempC);
  Serial.print(" °C ");


//  
  delay(2000);
}
