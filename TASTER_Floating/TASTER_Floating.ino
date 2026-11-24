const int tasterPin = 33;   

void setup() {
  Serial.begin(115200);
  pinMode(tasterPin, INPUT); 
}

void loop() {
  int wert = digitalRead(tasterPin);
  Serial.println(wert);
  delay(50);
}
