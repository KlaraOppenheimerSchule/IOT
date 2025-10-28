#include <Wire.h>

void setup() {
  Wire.begin(); // SDA und SCL automatisch oder z. B. Wire.begin(SDA, SCL);
  Serial.begin(115200);
  while (!Serial); // Warten auf Serial Monitor
  Serial.println("\nI2C Scanner gestartet...");
}

void loop() {
  byte error, address;
  int count = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C Gerät gefunden bei Adresse 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      count++;
    } else if (error == 4) {
      Serial.print("Unbekannter Fehler bei Adresse 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (count == 0)
    Serial.println("Keine I2C Geräte gefunden\n");
  else
    Serial.println("Scan abgeschlossen\n");

  delay(5000); // Alle 5 Sekunden erneut scannen
}
