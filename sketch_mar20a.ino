#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1015.h>
#include <DFRobot_ESP_EC.h>

#define ONE_WIRE_BUS 14 // GPIO pin 14 on ESP32 for OneWire temperature sensor
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;

float voltage, ecValue, temperature = 25;

String apiKey = "YE4Z7VI9CCW4TW1D"; // Enter your Write API key from ThingSpeak

const char *ssid = "Pixel 7"; // replace with your WiFi SSID
const char *pass = "sohan141296"; // replace with your WiFi password
const char *server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(32); // Initialize EEPROM to store calibration k
  ec.begin();
  sensors.begin();

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  voltage = analogRead(A0); // A0 is GPIO pin 36
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0); // Read temperature sensor to execute temperature compensation
  ecValue = ec.readEC(voltage, temperature); // Convert voltage to EC with temperature compensation

  Serial.print("Temperature:");
  Serial.print(temperature, 2);
  Serial.println("ºC");

  Serial.print("EC:");
  Serial.println(ecValue, 2);

  // Update ThingSpeak channel with temperature and EC values
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature, 2);
    postStr += "&field2=";
    postStr += String(ecValue, 2);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    delay(500); // Delay before closing connection
  }
  client.stop();

  delay(1500); // Delay between updates
}
