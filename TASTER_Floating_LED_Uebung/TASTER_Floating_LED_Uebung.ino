const int tasterPin = 33;   // Taster gegen GND, interner Pull-up
const int ledPin    = 32;   // LED über 330 Ω gegen GND

void setup() {
  Serial.begin(115200);
  pinMode(tasterPin, INPUT_PULLUP);  // internen Pull-up (~45 kΩ) aktivieren
  pinMode(ledPin, OUTPUT);           // LED-Pin als Ausgang
  digitalWrite(ledPin, LOW);         // LED zu Beginn aus
}

void loop() {
  int wert = digitalRead(tasterPin); // gedrückt = LOW, losgelassen = HIGH
  Serial.println(wert);

  if (wert == LOW) {
    digitalWrite(ledPin, HIGH);      // Taster gedrückt -> LED an
  } else {
    digitalWrite(ledPin, LOW);       // Taster losgelassen -> LED aus
  }
}