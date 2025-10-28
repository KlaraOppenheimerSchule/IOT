#define PIR_PIN 14  // GPIO 14

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  int motion = digitalRead(PIR_PIN);
  if (motion == HIGH) {
    Serial.println("Bewegung erkannt!");
  } else {
    Serial.println("Keine Bewegung.");
  }
  delay(1000);
}