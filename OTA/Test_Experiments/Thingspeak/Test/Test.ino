#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Samsung";
const char *password = "66778899";

const char *host = "api.thingspeak.com";
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
  Serial.println("Connection established with: api.thingspeak.com");
  // String randomString = String(random);
  String Link ="GET /update?api_key="+apiKey+"&field1=";
  Link = Link + String(5);
  Link = Link + "HTTP/1.1\r\n"+"HOST: "+host+"\r\n"+"Connection: closed";
  client.print(Link);
  delay(100);

  int timeout=0;
  
  while(client.available() && (timeout<1000))
  {
   delay(10);
    timeout++;
  }
  if(timeout<500) 
  {
    while(client.available())
    Serial.println(client.readString());
  } 
  else
  {
    Serial.println("Request Timeout..");
  }

  delay(5000);
}
