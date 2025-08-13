void setup() 
{ 
  pinMode(1, OUTPUT); //hier muss evtl 1 stat 2 stehen 
  digitalWrite(2, HIGH); // LED off! by making the voltage LOW 
} 

void loop() 
{ 
  digitalWrite(2, HIGH); // turn LED off! 
  delay(1000); // wait for a second 
  digitalWrite(2, LOW); // turn LED on! 
  delay(1000); // wait for a second 
} 

