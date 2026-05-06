 
const int motorPinA = 26;
const int motorPinB = 27;

void setup()
{
  Serial.begin(115200);
  pinMode(motorPinA, OUTPUT);
  pinMode(motorPinB, OUTPUT);
  Serial.print("Setup abgeschlossen");
}

void loop()
{
  digitalWrite(motorPinA, HIGH);
  digitalWrite(motorPinB, LOW);
  Serial.print("MotorPinA an");
  delay(2000);

  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  delay(500);

  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, HIGH);
  delay(2000);

  digitalWrite(motorPinA, LOW);
  digitalWrite(motorPinB, LOW);
  delay(500);
}