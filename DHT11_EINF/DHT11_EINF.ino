#include "DHT.h"

#define DHTPIN 4          // GPIO-Pin, an dem DATA angeschlossen ist
#define DHTTYPE DHT11     // Sensor-Typ

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(19200);
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Fehler beim Lesen vom DHT11!");
    delay(2000); // alle 2 Sekunden neue Messung
    return;
  }

  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.print(" °C, Luftfeuchtigkeit: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(2000); // alle 2 Sekunden neue Messung
}