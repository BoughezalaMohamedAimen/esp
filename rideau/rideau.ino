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

// arduino json 5.13.2
void setup() {
  pinMode(up, OUTPUT); 
  pinMode(down, OUTPUT);

  Serial.begin(115200);

  SPIFFS.begin();

  wifiConnect();

  server.on("/changeSettings",changeSettings);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/", handleRoot);
  server.on("/up", handleUp);
  server.on("/pause", handlePause);
  server.on("/down", handleDown);


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();//Handle client requests
  delay(500);
}
