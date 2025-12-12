const int ledPin =1;

void setup() 
{ 
  pinMode(ledPin, OUTPUT); // Pin1 wird auf pinmode output gesetzt
  digitalWrite(1, HIGH); // LED wird ausgeschalten, idem die Spannung angelegt wird
  
  /* Erklärung zu low und high:
  Die interne LED des ESP32 leuchtet bei digitalWrite(1, LOW);, weil sie active low geschaltet ist 
  das bedeutet, sie wird eingeschaltet, wenn der zugehörige GPIO-Pin auf LOW (0 V) gesetzt wird, da 
  dann Strom von VCC über die LED zum Pin fließen kann.
  */
} 

void loop() 
{ 
  //Start "S" (kurz)
  digitalWrite(1, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(1, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 

  digitalWrite(1, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 


//Start "0" (lang)
  digitalWrite(1, LOW); // turn LED on! 
  delay(3000); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(1, LOW); // turn LED on! 
  delay(3000); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(1, LOW); // turn LED on! 
  delay(3000); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 


  //Start "S" (kurz)
  digitalWrite(1, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 
  
  digitalWrite(1, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 

  digitalWrite(1, LOW); // turn LED on! 
  delay(500); 
  digitalWrite(1, HIGH); // turn LED off! 
  delay(500); 
 } 

