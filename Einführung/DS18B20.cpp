#include <OneWire.h>
#include <DallasTemperature.h>

// Datenpin des DS18B20 (z. B. GPIO 2)
#define ONE_WIRE_BUS 2

// Setup OneWire und DallasTemperature
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin(); // Sensor initialisieren
}

void loop() {
  // Temperatur anfordern
  sensors.requestTemperatures(); 

  // Temperatur in °C auslesen
  float tempC = sensors.getTempCByIndex(0); 

  Serial.print("Temperatur: ");
  Serial.print(tempC);
  Serial.println(" °C");

  delay(1000); // 1 Sekunde warten
}
