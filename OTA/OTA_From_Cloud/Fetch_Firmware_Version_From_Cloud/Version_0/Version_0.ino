#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include "credentials.h"


float version;

void FetchFirmwareVersion();
void ConnectToWiFi();
void setup()
{
  Serial.begin(115200);
  connectToWiFi();
}

void loop()
{
  Serial.println("Running: Version_0");
  FetchFirmwareVersion();
  delay(500);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);

  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
}
  Serial.println("\nConnected to WiFi");
}

void FetchFirmwareVersion()
{
WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "https://sumitadep002.github.io/firmware.json")) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
    }
  

  delay(1000);
}
