#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);        
#include <DNSServer.h>           
#include <WiFiManager.h>         

void setup() 
{
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Fruit", "12345678");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();
}

void loop() 
{
}
