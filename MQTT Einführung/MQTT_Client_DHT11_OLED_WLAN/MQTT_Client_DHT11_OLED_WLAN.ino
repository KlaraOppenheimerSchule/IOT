// ====== DHT11 ======
#include "DHT.h"

// ====== OLED ======
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ====== WLAN & MQTT ======
#include <WiFi.h>
#include <PubSubClient.h>

// ---- Pins & Typen ----
#define DHTPIN   14
#define DHTTYPE  DHT11

// ---- OLED-Attribute ----
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT  64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---- DHT-Objekt ----
DHT dht(DHTPIN, DHTTYPE);

// ---- WLAN-Zugangsdaten (anpassen!) ----
const char* WIFI_SSID = "TO BE ADDED";
const char* WIFI_PSK  = "TO BE ADDED";

// ---- MQTT-Broker ----
const char* MQTT_HOST = "test.mosquitto.org";
const uint16_t MQTT_PORT = 1883; // unverschlüsselt (für TLS siehe unten)
const char* TOPIC_TEMP = "esp32/temperature";
const char* TOPIC_HUM  = "esp32/humidity";
const char* TOPIC_JSON = "esp32/telemetry";

// ---- Netzwerkobjekte ----
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

// ---- Publish-Taktung ----
const uint32_t PUBLISH_INTERVAL_MS = 10000;
uint32_t lastPublish = 0;

// ====== Hilfsfunktionen ======
void connectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  Serial.print("WLAN verbinden");
  uint8_t dots = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (++dots % 12 == 0) Serial.println();
  }
  Serial.println();
  Serial.print("WLAN verbunden, IP: ");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  mqtt.setServer(MQTT_HOST, MQTT_PORT);

  while (!mqtt.connected()) {
    String clientId = "esp32-dht11-" + String((uint32_t)ESP.getEfuseMac(), HEX);
    Serial.print("MQTT verbinden als ");
    Serial.print(clientId);
    Serial.print(" ... ");
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("OK");
      // Optional: hier Subscribes setzen, falls benötigt
    } else {
      Serial.printf("Fehler rc=%d -> retry in 3s\n", mqtt.state());
      delay(3000);
    }
  }
}

void showOnOLED(float t, float h) {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 8);
  oled.println("DHT11");
  oled.setCursor(0, 24);
  oled.print("Temp: "); oled.print(t, 1); oled.println(" C");
  oled.setCursor(0, 40);
  oled.print("Hum : "); oled.print(h, 1); oled.println(" %");
  oled.display();
}

void publishReadings(float t, float h) {
  // Einzelwerte
  char bufT[16]; dtostrf(t, 0, 2, bufT);
  char bufH[16]; dtostrf(h, 0, 2, bufH);

  bool ok1 = mqtt.publish(TOPIC_TEMP, bufT);
  bool ok2 = mqtt.publish(TOPIC_HUM,  bufH);

  // JSON kombiniert
  char json[96];
  snprintf(json, sizeof(json), "{\"temperature\":%.2f,\"humidity\":%.2f}", t, h);
  bool ok3 = mqtt.publish(TOPIC_JSON, json);

  Serial.printf("Publish %s=%s [%s], %s=%s [%s], %s=%s [%s]\n",
    TOPIC_TEMP, bufT, ok1 ? "OK" : "ERR",
    TOPIC_HUM,  bufH, ok2 ? "OK" : "ERR",
    TOPIC_JSON, json,  ok3 ? "OK" : "ERR");
}

// ====== Arduino Standardfunktionen ======
void setup() {
  Serial.begin(19200);

  // DHT starten
  dht.begin();

  // OLED initialisieren
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1) delay(1);
  }
  Wire.begin(); // I2C sicherheitshalber initialisieren

  // Bootmeldung
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("Setup...");
  oled.display();

  // WLAN & MQTT
  connectWiFi();
  connectMQTT();
}

void loop() {
  // Verbindungen aufrecht halten
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  // Lesen & Publizieren im Intervall
  uint32_t now = millis();
  if (now - lastPublish >= PUBLISH_INTERVAL_MS) {
    lastPublish = now;

    float temp = dht.readTemperature(); // Celsius
    float hum  = dht.readHumidity();
    if (isnan(temp) || isnan(hum)) {
      Serial.println("Fehler beim Lesen vom DHT11!");
      return;
    }

    Serial.printf("Temperatur: %.2f C, Luftfeuchte: %.2f %%\n", temp, hum);
    showOnOLED(temp, hum);
    publishReadings(temp, hum);
  }
}
