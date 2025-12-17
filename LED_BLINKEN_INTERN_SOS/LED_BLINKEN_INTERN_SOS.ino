const int ledPin =1;

void setup() 
{ 
  pinMode(ledPin, OUTPUT); // Pin1 wird auf pinmode output gesetzt
  digitalWrite(ledPin, HIGH); // LED wird ausgeschalten, idem die Spannung angelegt wird
} 

void loop() 
{ 
  //Start "S" (kurz)
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(500); 

  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(1000); 

  //Start "0" (lang)
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(3000); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(3000); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(3000); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(1000); 


  //Start "S" (kurz)
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(500); 

  digitalWrite(ledPin, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(ledPin, HIGH); // turn LED off! 
  delay(3000);
 } 

