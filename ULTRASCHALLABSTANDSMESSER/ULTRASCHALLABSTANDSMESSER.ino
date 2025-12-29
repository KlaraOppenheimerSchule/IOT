const int TRIGGER_PIN = 5; //D5
const int ECHO_PIN = ; //D4
 
long dauer=0; //Dauer = Variable, Zeit wird gespeichert, die eine Schallwelle bis zur Reflektion und zurück benötigt. Startwert ist hier 0.
long entfernung=0; //entfernung = variable („long“ damit größere Zahl gespeichert werden kann)

void setup() {
  Serial.begin(9600); // Serielle Kommunikation starten
  pinMode(TRIGGER_PIN, OUTPUT); //Trigger-Pin als Ausgang festlegen
  pinMode(ECHO_PIN, INPUT); //Echo-Pin ist als Eingang festlegen 
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW); //kurze Zeit Spannung weg vom Trigger-Pin. Damit später beim senden des Trigger-Signals dieser rauschfreie ist.
  delayMicroseconds(5); //Dauer: 5 Mikrosekunden
  digitalWrite(TRIGGER_PIN, HIGH); //Jetzt Ultraschallwelle lossenden.
  delayMicroseconds(10); //Das Senden erfolgt für 10 Mikrosekunden.
  digitalWrite(TRIGGER_PIN, LOW); //Dann wird das Senden beendet.
  
  dauer = pulseIn(ECHO_PIN, HIGH);  //Mikrocontroller zählt Zeit in Mikrosekunden, bis der Schall zum Ultraschallsensor zurückkehrt.
  
  entfernung = (dauer/2) * 0.03432; //Entfernung berechnen in Zentimetern. Man teilt zunächst die Zeit durch zwei (Weil man ja nur eine Strecke berechnen möchte und nicht die Strecke hin- und zurück). Den Wert multipliziert man mit der Schallgeschwindigkeit in der Einheit Zentimeter/Mikrosekunde und erhält dann den Wert in Zentimetern.
  
  if (entfernung >= 500 || entfernung <= 0) 
  {
    Serial.println(entfernung);
    Serial.println(dauer);
    Serial.println("Kein Messwert"); //Wenn Entfernung über 500cm oder unter 0cm liegt - falsch / ungenau
  }
  else
  {
    Serial.print(entfernung); //Falls nicht: Entfernung ausgegeben
    Serial.println(" cm"); // Ausgabe der Einheit "cm"
  }
    
  delay(1000); // 1 Sekunde Pause
}


