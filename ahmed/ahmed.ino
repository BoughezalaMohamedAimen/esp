#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>

#include "global_variables.h"
#include "templates.h"
#include "functions.h"
#include "views.h"


void setup() {
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);

  Serial.begin(115200);

  SPIFFS.begin();

  wifiConnect();

  server.on("/changeSettings",changeSettings);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/", handleRoot);
  server.on("/toogle/1", handleToggle1);
  server.on("/toogle/2", handleToggle2);
  server.on("/toogle/3", handleToggle3);
  server.on("/toogle/4", handleToggle4);
  server.on("/toogle/5", handleToggle5);
  server.on("/toogle/6", handleToggle6);
  server.on("/toogle/7", handleToggle7);
  server.on("/toogle/8", handleToggle8);


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();//Handle client requests
  delay(1000);

}
