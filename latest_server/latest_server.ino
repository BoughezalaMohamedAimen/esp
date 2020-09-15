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

  Serial.begin(115200);

  SPIFFS.begin();

  wifiConnect();

  server.on("/changeSettings",changeSettings);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/", handleRoot);


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  Serial.println(" code response :");
  Serial.println(DoGet("http://google.com"));
  Serial.println(" result response :");
  Serial.println(request_result);
  server.handleClient();//Handle client requests
  delay(1000);

}
