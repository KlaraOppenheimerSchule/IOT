//Libary for DHT11
#include "DHT.h"

//Libaries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//PINS for DHT11
#define DHTPIN 14        
#define DHTTYPE DHT11     

//Attributes for OLED
#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

//Create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(19200);

  //OLED DISPLAY SETUP
  //initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 10);       // set position to display
  oled.println("Setup..."); // set text
  oled.display();   
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Fehler beim Lesen vom DHT11!");
    delay(2000); 
    return;
  }

  Serial.print("Temperatur: ");
  Serial.print(temp);
  Serial.print(" °C, Luftfeuchtigkeit: ");
  Serial.print(hum);
  Serial.println(" %");

  oled.clearDisplay();
  oled.setCursor(0, 10);  
  oled.println("Temperatur:");
  oled.println(temp);
  oled.println("Luftfeuchtigkeit:");
  oled.println(hum);
  oled.display();

  delay(2000); 
}



