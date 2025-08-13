const int ledPin = 2;           // Onboard-LED (GPIO 2)
const int freq = 5000;          // PWM-Frequenz in Hz
const int ledChannel = 0;       // PWM-Kanal (0–15)
const int resolution = 8;       // 8-Bit-Auflösung (0–255)

void setup() {
  Serial.begin(115200);         // Serielle Kommunikation starten
  ledcSetup(ledChannel, freq, resolution);   // PWM konfigurieren
  ledcAttachPin(ledPin, ledChannel);         // PWM-Kanal mit GPIO verbinden
  Serial.println("PWM-LED-Dimmung gestartet");
}

void loop() {
  // LED heller werden lassen
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledChannel, dutyCycle);
    Serial.print("Helligkeit: ");
    Serial.println(dutyCycle);
    delay(10);
  }

  // LED dunkler werden lassen
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledChannel, dutyCycle);
    Serial.print("Helligkeit: ");
    Serial.println(dutyCycle);
    delay(10);
  }
}
