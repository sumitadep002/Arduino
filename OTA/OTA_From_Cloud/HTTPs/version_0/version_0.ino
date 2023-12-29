#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

const char* ssid = "Samsung";
const char* password = "66778899";
const char* jsonURL = "https://sumitadep002.github.io/firmware.json";
const char* fingerprint = "01:23:45:67:89:AB:CD:EF:01:23:45:67:89:AB:CD:EF:01:23:45:67";

void Connect_To_Wifi();
void Fetch_Firmware_Version();

void setup() {
  Serial.begin(115200);
  Connect_To_Wifi();
}

void loop() {
  Fetch_Firmware_Version();
  delay(1000);
}

void Connect_To_Wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void Fetch_Firmware_Version() {
  BearSSL::WiFiClientSecure client;
  client.setFingerprint(fingerprint);

  if (client.connect(jsonURL, 443)) {
    client.print(String("GET ") + jsonURL + " HTTP/1.1\r\n" +
                 "Host: " + jsonURL + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Wait for the server's response
    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
  }

  client.stop();
}
