//Libary for DHT11
#include "DHT.h"

//PINS for DHT11
#define DHTPIN 14        
#define DHTTYPE DHT11     

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(19200);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Fehler beim Lesen vom DHT11!");
    delay(2000); 
    return;
  }

  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.print(" °C, Luftfeuchtigkeit: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(2000); 
}