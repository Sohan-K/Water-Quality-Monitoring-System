#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1015.h>
#include <DFRobot_ESP_EC.h>

#define ONE_WIRE_BUS 14 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;

float voltage, ecValue, temperature = 25;

String apiKey = "YE4Z7VI9CCW4TW1D"; 

const char *ssid = "Pixel 7"; 
const char *pass = "sohan141296"; 
const char *server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(32); 
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
  voltage = analogRead(A0); 
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0); 
  ecValue = ec.readEC(voltage, temperature); 
  Serial.print("Temperature:");
  Serial.print(temperature, 2);
  Serial.println("ºC");

  Serial.print("EC:");
  Serial.println(ecValue, 2);

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

    delay(500); 
  }
  client.stop();

  delay(1500); 
}
