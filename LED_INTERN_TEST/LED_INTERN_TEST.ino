void setup() {
  for (int pin = 0; pin < 40; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    serial.
    delay(100);
    digitalWrite(pin, LOW);
    delay(100);
  }
}

void loop() {
  // leer
}
