#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Samsung";
const char *password = "66778899";

const char *host = "https://sumitadep002.github.io";
String apiKey = "7V75UUB51ZV58IE6";


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("Connecting to Wifi");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("WIFI Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client;
  const int httpPort = 80;
  while(!client.connect(host, httpPort))
  {
    Serial.println("Connection Failed");
    delay(500);
  }
  Serial.print("Connection established with: ");
  Serial.println(host);
  delay(100);
  
     while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
    Serial.println();

  delay(5000);
}
