//Doc: https://docs.arduino.cc/language-reference/en/functions/wifi/wificlass/

#include <WiFi.h>

// ===== Zugangsdaten =====
const char* ssid = "FBIT.IoT.Router6";
const char* password = "WueLoveIoT";

// ===== LED Pin (z.B. Onboard LED meist GPIO 2) =====
const int ledPin = 2;

// ===== Timeout (15 Sekunden) =====
const unsigned long timeout = 15000;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  Serial.println("\n--- WLAN-Verbindung wird gestartet ---");

  connectToWiFi();
}

void loop() {
  // Falls Verbindung verloren geht → neu verbinden
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nVerbindung verloren! Neuer Versuch...");
    connectToWiFi();
  }
}

// ===== Funktion zum Verbinden =====
void connectToWiFi() {
  WiFi.begin(ssid, password);

  unsigned long startTime = millis();

  Serial.print("Verbinde mit WLAN");

  bool ledState = false;

  // solange nicht verbunden UND Timeout nicht überschritten
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < timeout) {

    // LED blinkt während Verbindungsaufbau
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    Serial.print(".");
    delay(500);
  }

  // ===== Auswertung =====
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(ledPin, HIGH);  // LED dauerhaft AN

    Serial.println("\n Verbindung erfolgreich hergestellt!");
    Serial.print("IP-Adresse: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signalstärke (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

  } else {
    digitalWrite(ledPin, LOW);

    Serial.println("\n Zeitüberschreitung – Verbindung fehlgeschlagen!");
    Serial.println("Neuer Versuch in 5 Sekunden...");
    delay(5000);

    // automatischer Wiederholversuch
    connectToWiFi();
  }
}
