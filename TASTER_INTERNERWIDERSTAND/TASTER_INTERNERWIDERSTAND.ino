
#define LED_PIN    1      // interne LED (ESP32)
#define BUTTON_PIN 18     // Taster-Pin

void setup() {
  pinMode(LED_PIN, OUTPUT);                // LED als Ausgang
  pinMode(BUTTON_PIN, INPUT_PULLUP);       // Taster mit internem Pull-up
}

void loop() {
  // Taster lesen (LOW = gedrückt, HIGH = nicht gedrückt)
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, LOW);           // LED aus
  } else {
    digitalWrite(LED_PIN, HIGH);            // LED an
  }
}


/*Hinweise
Wie funktioniert der intere Widerstand:
INPUT_PULLUP: Wenn du den Pin als INPUT_PULLUP setzt, aktiviert der Mikrocontroller einen internen Widerstand, der den Pin mit Plus (HIGH) verbindet.
Das bedeutet: Wenn der Taster nicht gedrückt ist, ist der Eingang automatisch HIGH.

Taster gegen GND: Der Taster ist so angeschlossen, dass er beim Drücken den Pin mit Masse (GND) verbindet.
Drückst du den Taster, wird der Eingang auf LOW gezogen.

Logik im Programm: Wenn der Eingang LOW ist → Taster gedrückt → LED einschalten.
Wenn der Eingang HIGH ist → Taster nicht gedrückt → LED ausschalten.

Warum leuchtet die interne LED bei low:
Die LED leuchtet bei LOW, weil sie so angeschlossen ist:​
Anode (Pluspol) der LED ist über einen Vorwiderstand mit der Versorgungsspannung (z. B. +5 V) verbunden.​
Kathode (Minuspol) geht zum Mikrocontroller-Pin.​
Wenn der Pin LOW (0 V) ist, liegt zwischen Anode (+5 V) und Kathode (0 V) eine Spannung → Strom fließt → LED leuchtet.​
Wenn der Pin HIGH (+5 V) ist, haben beide Seiten fast die gleiche Spannung → kein Strom → LED bleibt aus.​
Das nennt man aktive-LOW-Schaltung, weil der Pin nicht Strom liefert, sondern ihn zur Masse „zieht“
*/

