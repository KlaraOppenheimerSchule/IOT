int LED_EXTERN = 23;

void setup() {
  Serial.begin(9600);
  pinMode(LED_EXTERN, OUTPUT);
}

void loop() {
  digitalWrite(LED_EXTERN, HIGH);  
  delay(1000);                      
  digitalWrite(LED_EXTERN, LOW);   
  delay(1000);                     
}
