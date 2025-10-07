void setup() 
{ 
  pinMode(1, OUTPUT); // SET pin 1 in pinmode output
  digitalWrite(1, HIGH); // LED off! by making the voltage LOW 
} 

void loop() 
{ 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(1000); // wait for a second 
  digitalWrite(1, LOW); // turn LED on! 
  delay(1000); // wait for a second 
} 

