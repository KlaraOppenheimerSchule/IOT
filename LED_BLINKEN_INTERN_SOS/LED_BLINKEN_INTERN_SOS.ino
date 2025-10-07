const int ledPin =1;

void setup() 
{ 
  pinMode(ledPin, OUTPUT); // SET pin 1 in pinmode output
  digitalWrite(1, HIGH); // LED off! by making the voltage LOW 
  
  /* Erklärung zu low und high:
  Die interne LED des ESP32 leuchtet bei digitalWrite(1, LOW);, weil sie active low geschaltet ist 
  das bedeutet, sie wird eingeschaltet, wenn der zugehörige GPIO-Pin auf LOW (0 V) gesetzt wird, da 
  dann Strom von VCC über die LED zum Pin fließen kann.
  */
} 

void loop() 
{ 
  //Start long
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
  //End long

//Start short
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
  //End short


  //Start long
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
  //End long
 } 

