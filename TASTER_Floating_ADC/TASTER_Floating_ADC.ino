const int tasterPin = 34;

void setup() {
  Serial.begin(115200);
  pinMode(tasterPin, INPUT);
}

void loop() {
  int wechsel = 0;
  int alt = digitalRead(tasterPin);
  for (int i = 0; i < 10000; i++) {      // ~10.000 schnelle Messungen
    int neu = digitalRead(tasterPin);
    if (neu != alt) wechsel++;
    alt = neu;
  }
  Serial.println(wechsel);               // > 0 = Pin kippt = Floating
  delay(100);
}