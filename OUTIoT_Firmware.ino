#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

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
  Serial.begin(115200);
  updatePasscodeAndSSID();
}

void loop() {
  server.handleClient();
}

void updatePasscodeAndSSID(){
    WiFiManager wifiManager;
    wifiManager.autoConnect("OUTIoT_WiFi_Setup", "masterpassword"); //TODO Test to make sure multiple modules don't interfere with eachother.
}
