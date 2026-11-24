/*
 * Erweiterung für Schnelle: LED dimmen mit PWM
 * Board: ESP32 (Arduino-Core 3.x)
 *
 * Die LED wird langsam heller und danach wieder dunkler.
 */

const int LED_PIN    = 1;     // Pin der LED
const int PWM_FREQ   = 5000;  // 5000 Hz -> kein sichtbares Flackern
const int PWM_BITS   = 8;     // 8 Bit -> Werte von 0 bis 255
const int SCHRITT_MS = 8;     // Tempo des Dimmens

void setup() {
  ledcAttach(LED_PIN, PWM_FREQ, PWM_BITS);   // PWM am Pin einschalten
}

void loop() {
  for (int wert = 0; wert <= 255; wert++) {  // heller
    ledcWrite(LED_PIN, wert);
    delay(SCHRITT_MS);
  }
  for (int wert = 255; wert >= 0; wert--) {  // dunkler
    ledcWrite(LED_PIN, wert);
    delay(SCHRITT_MS);
  }
  delay(500);
}