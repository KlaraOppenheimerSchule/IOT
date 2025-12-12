// Library for DHT11
#include "DHT.h"

// Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- WLAN (ESP32) ---
#include <WiFi.h>
const char* WIFI_SSID = "DEINE_SSID";
const char* WIFI_PASS = "DEIN_PASSWORT";

// PINS for DHT11
#define DHTPIN 14
#define DHTTYPE DHT11

// Attributes for OLED
#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

// Create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(19200);

  // OLED DISPLAY SETUP
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  // DHT starten
  dht.begin();

  // --- WLAN: möglichst schlicht ---
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Verbinde mit WLAN: "); Serial.println(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WLAN verbunden, IP: ");
  Serial.println(WiFi.localIP());

  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("Setup...");
  oled.display();
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

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

  // Optional: WLAN-Status klein unten
  oled.setCursor(0, 54);
  if (WiFi.status() == WL_CONNECTED) {
    oled.print("IP: ");
    oled.print(WiFi.localIP());
  } else {
    oled.print("WLAN: offline");
  }

  oled.display();
  delay(2000);
}
