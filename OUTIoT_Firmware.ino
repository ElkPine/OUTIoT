#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "OUTIoT_Module"
#define APPSK  "adminIoT"
#endif

IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,254);
IPAddress subnet(255,255,255,0);

/* Bootup credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

void setup() {
  //TODO Add EEPROM checker for saved SSID & Passcode
  Serial.begin(115200);
  updatePasscodeAndSSID();
}

void loop() {
  server.handleClient();
}

void updatePasscodeAndSSID(){
  Serial.println("StartingSoftAP...");
  
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  WiFi.softAP(ssid, password);

  //TODO Retrieve SSID and Password from user
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}
