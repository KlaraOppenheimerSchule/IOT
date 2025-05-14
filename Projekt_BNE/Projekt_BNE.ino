#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <MQTT.h>
#include <time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define I2C_SDA 16
#define I2C_SCL 17

const char* ssid = "FBIT.IoT.Router7";
const char* password = "WueLoveIoT";

const char* mqttBroker = "192.168.108.14";
const int mqttPort = 1883;
const char* mqttClientID = "ESP32Client1";

const char* topicData = "Wuerzburg1/KOS/A105/data";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0;

#define SEALEVELPRESSURE_HPA (1017)
Adafruit_BME280 bme;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;
const unsigned long publishInterval = 10000;

void connectToWiFi() {
Serial.print("Connecting to Wi-Fi");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("\nWi-Fi connected.");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}

void connectToMQTT() {
Serial.print("Connecting to MQTT broker...");
client.begin(mqttBroker, mqttPort, net);
while (!client.connect(mqttClientID)) {
Serial.print(".");
delay(1000);
}
Serial.println("\nConnected to MQTT broker.");
}

String getFormattedTime() {
struct tm timeinfo;
if (!getLocalTime(&timeinfo)) {
Serial.println("Failed to obtain time");
return "";
}
char buffer[25];
strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
return String(buffer);
}

// Optional I2C scan (for debugging)
void scanI2C() {
byte count = 0;
Serial.println("Scanning I2C devices...");
for (byte addr = 1; addr < 127; addr++) {
Wire.beginTransmission(addr);
if (Wire.endTransmission() == 0) {
Serial.print("I2C device found at 0x");
if (addr < 16) Serial.print("0");
Serial.println(addr, HEX);
count++;
}
}
if (count == 0) Serial.println("❌ No I2C devices found!");
else Serial.println("✅ I2C scan complete.");
}

void setup() {
Serial.begin(115200);
delay(1000);
Wire.begin(I2C_SDA, I2C_SCL);

// Optional: Run I2C scan
scanI2C();

if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
Serial.println(F("SSD1306 allocation failed"));
while (true);
}

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Initializing...");
display.display();

if (!bme.begin(0x76)) {
Serial.println("❌ BME280 not found!");
display.clearDisplay();
display.setCursor(0, 0);
display.println("BME280 not found!");
display.display();
while (true);
}

connectToWiFi();
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

// Wait for time sync
struct tm timeinfo;
while (!getLocalTime(&timeinfo)) {
Serial.println("Waiting for time sync...");
delay(1000);
}

connectToMQTT();
client.loop();

display.clearDisplay();
display.setCursor(0, 0);
display.println("Setup Complete");
display.display();
}

void loop() {
if (WiFi.status() != WL_CONNECTED) {
connectToWiFi();
}

if (!client.connected()) {
connectToMQTT();
}

client.loop();
delay(10);

if (millis() - lastMillis > publishInterval) {
lastMillis = millis();

float temperature = bme.readTemperature();
float humidity = bme.readHumidity();
float pressure = bme.readPressure() / 100.0F;
String timestamp = getFormattedTime();

if (timestamp == "") {
Serial.println("Skipping publish due to invalid time.");
return;
}

String payload = "{";
payload += "\"temp\":" + String(temperature, 2) + ",";
payload += "\"hum\":" + String(humidity, 2) + ",";
payload += "\"time\":\"" + timestamp + "\",";
payload += "\"pressure\":" + String(pressure, 2) + ",";
payload += "\"location\":\"wuerzburg\",";
payload += "\"group\":\"group1\"";
payload += "}";

if (client.publish(topicData, payload.c_str())) {
Serial.print("Data published: ");
Serial.println(payload);
} else {
Serial.println("❌ Failed to publish data.");
}

display.clearDisplay();
display.setTextSize(1);
display.setCursor(0, 0);
display.print("Temp: ");
display.print(temperature, 1);
display.println(" C");

display.print("Hum : ");
display.print(humidity, 1);
display.println(" %");

display.print("Pres: ");
display.print(pressure, 1);
display.println(" hPa");

display.println("");
display.println(timestamp);
display.display();
}
}


