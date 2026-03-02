// Pinbelegung
const int ENA = 25;   // PWM / Enable
const int IN1 = 26;   // Richtung
const int IN2 = 27;   // Richtung

// PWM-Einstellungen
const int PWM_CHANNEL = 0;
const int PWM_FREQ = 20000;  // 20 kHz
const int PWM_RES  = 8;      // 0..255

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);
  ledcAttachPin(ENA, PWM_CHANNEL);
}

void loop() {
  // Motor starten (Vorwärts)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(PWM_CHANNEL, 200);  // Geschwindigkeit (0–255)

  delay(5000);   // 5 Sekunden Laufzeit

  // Motor stoppen
  ledcWrite(PWM_CHANNEL, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  delay(2000);   // 2 Sekunden warten
}