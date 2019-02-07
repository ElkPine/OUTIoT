#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

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

boolean outletState1 = false;
boolean outletState2 = false;

void setup() {
  Serial.begin(115200);
  updatePasscodeAndSSID();
  startHTTPServer();
}

void loop() {
  server.handleClient();
}

void startHTTPServer(){
  server.on("/control", handleRequest);
  server.begin();
  Serial.println("HTTP Server Started and Listening");
}

void handleRequest(){
  if (server.hasArg("json") == false){
    server.send(200, "text/json", "Body not received");
    Serial.println("[RESTful] Received something..but an error occured..");
    return;
  }

  if(server.arg("json").equals("Elkpine Verified")){
    server.send(200, "text/json", "CORRECT");
  }else{
    server.send(200, "text/json", "Incorrect Verification");
    return;
  }
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
