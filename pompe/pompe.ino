#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>

#include "global_variables.h"
#include "templates.h"
#include "functions.h"
#include "views.h"


void setup() {
  pinMode(relay, OUTPUT);

  Serial.begin(115200);

  SPIFFS.begin();

  wifiInit();

  server.on("/changeSettings",changeSettings);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

}
