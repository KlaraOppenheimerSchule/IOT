#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define I2C_SCL 21
#define I2C_SDA 22

Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(9600);
  delay(1000); // kurze Pause für den seriellen Monitor

  // I2C initialisieren
  Wire.begin(I2C_SDA, I2C_SCL);

  // BME280 initialisieren
  if (!bme.begin(0x76)) { // Standardadresse ist 0x76 oder 0x77
    Serial.println("BME280 nicht gefunden! Bitte Verkabelung prüfen.");
    while (1);
  }

  Serial.println("BME280 Sensor initialisiert.");
}

void loop() {
  float temperatur = bme.readTemperature(); // Temperatur in °C
  float pressure = bme.readPressure();
  float humidity= bme.readHumidity();

  Serial.print("Temperatur: ");
  Serial.print(temperatur);
  Serial.println(" °C");

  Serial.print("Luftdruck: ");
  Serial.print(pressure);
  Serial.println(" PA");

  Serial.print("Luftfeuchtigkeit: ");
  Serial.print(humidity);
  Serial.println(" %");



  delay(2000); // alle 2 Sekunden aktualisieren
}
