#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#ifndef APSSID
#define APSSID "OUTIoT_Module"
#define APPSK  "adminIoT"
#endif

/* Bootup credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  updatePasscodeAndSSID();
  startHTTPServer();
}

void loop() {
  server.handleClient();
}

void startHTTPServer(){
  server.on("/validate", handleRequest);
  server.begin();
  Serial.println("HTTP Server Started and Listening");
}

void handleRequest(){
  if (server.hasArg("plain")== false){
    server.send(200, "text/plain", "Body not received");
    return;
  }

  String message = "Body received:\n";
  message += server.arg("plain");
  message += "\n";

  server.send(200, "text/plain", "CORRECT");
  Serial.println(message);
}

void updatePasscodeAndSSID(){
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.autoConnect("OUTIoT_WiFi_Setup", "masterpassword"); //TODO Test to make sure multiple modules don't interfere with eachother.
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());

  Serial.println(myWiFiManager->getConfigPortalSSID());
  // TODO: Blink LED in indication
}
