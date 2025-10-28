#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22); // SDA/SCL

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED nicht gefunden");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  for (int i = 1; i <= 100; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);
    
    if (i < 10) {
      display.print("0");
    }
    display.print(i);
    // Daten über I2C senden
    display.display(); 
    Serial.print("Zähler: ");
    Serial.println(i);
    delay(500); 
  }
}