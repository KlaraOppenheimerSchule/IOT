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

// ---- OLED ----
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---- DHT ----
DHT dht(DHTPIN, DHTTYPE);

// ---- WLAN-Zugangsdaten ----
const char* WIFI_SSID = "DEINE_SSID";
const char* WIFI_PASS = "DEIN_PASSWORT";

// ---- MQTT-Broker ----
const char* MQTT_HOST = "192.168.178.74";     // z.B. MQTT auf Raspberry
const uint16_t MQTT_PORT = 1883;              // unverschlüsselt
const char* TOPIC_JSON = "esp32/telemetry";   // Ziel-Topic für JSON

// ---- Netzwerkobjekte ----
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

void setup() {
  Serial.begin(19200);
  dht.begin();

  // OLED init
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED Fehler"));
    while (1);
  }
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);
  oled.println("Setup...");
  oled.display();

  // WLAN verbinden (einfach)
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Verbinde mit WLAN");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WLAN OK, IP: ");
  Serial.println(WiFi.localIP());

  // MQTT verbinden
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  connectMQTT();
}

void connectMQTT() {
  while (!mqtt.connected()) {
    String clientId = "esp32-dht11-" + String((uint32_t)ESP.getEfuseMac(), HEX);
    Serial.print("MQTT verbinden als "); Serial.print(clientId); Serial.print(" ... ");
    if (mqtt.connect(clientId.c_str())) {
      Serial.println("OK");
    } else {
      Serial.print("Fehler rc="); Serial.print(mqtt.state()); Serial.println(" -> retry in 3s");
      delay(3000);
    }
  }
}

void loop() {
  // Verbindungen sicherstellen
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    delay(500);
  }
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  // Sensor lesen
  float temp = dht.readTemperature();   // °C
  float hum  = dht.readHumidity();      // %
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Fehler beim Lesen vom DHT11!");
    delay(2000);
    return;
  }

  // Seriell ausgeben
  Serial.printf("Temperatur: %.2f C, Luftfeuchte: %.2f %%\n", temp, hum);

  // OLED anzeigen
  oled.clearDisplay();
  oled.setCursor(0, 10);
  oled.println("Temperatur:");
  oled.println(temp);
  oled.println("Luftfeuchtigkeit:");
  oled.println(hum);
  oled.setCursor(0, 54);
  oled.print("IP: "); oled.print(WiFi.localIP());
  oled.display();

  // --- JSON bilden & publish (ohne zusätzliche Libraries) ---
  // Puffer groß genug wählen; snprintf sichert gegen Überlauf ab.
  char json[96];
  snprintf(json, sizeof(json),
           "{\"temperature\":%.2f,\"humidity\":%.2f}", temp, hum);

  // Publish (QoS 0, kein Retain — minimal gehalten)
  if (mqtt.publish(TOPIC_JSON, json)) {
    Serial.print("MQTT -> "); Serial.print(TOPIC_JSON);
    Serial.print(" : "); Serial.println(json);
  } else {
    Serial.println("MQTT publish fehlgeschlagen");
  }

  delay(5000);  // Publish-Intervall
