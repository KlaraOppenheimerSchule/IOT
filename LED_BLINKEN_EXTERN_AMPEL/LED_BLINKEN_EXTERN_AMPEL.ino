#define REDLED    25
#define YELLOWLED 26
#define GREENLED  27

void setup() {
  pinMode(REDLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
}

void loop() {
  digitalWrite(REDLED, HIGH);
  delay(3000);
  digitalWrite(REDLED, LOW);

  digitalWrite(YELLOWLED, HIGH);
  delay(1000);
  digitalWrite(YELLOWLED, LOW);

  digitalWrite(GREENLED, HIGH);
  delay(3000);
  digitalWrite(GREENLED, LOW);

  digitalWrite(YELLOWLED, HIGH);
  delay(1000);
  digitalWrite(YELLOWLED, LOW);
}
