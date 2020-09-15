#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


#include "global_variables.h"
#include "templates.h"
#include "functions.h"
#include "views.h"


void setup() {

  Serial.begin(115200);

  SPIFFS.begin();
  irsend.begin();
  wifiConnect();

  server.on("/changeSettings",changeSettings);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/red", red);
  server.on("/green", green);
  server.on("/white", white);
  server.on("/blue", blue);
  server.on("/orangered", orangered);
  server.on("/orangeyellow", orangeyellow);
  server.on("/yellow", yellow);
  server.on("/yellowgreen", yellowgreen);
  server.on("/bluegreen", bluegreen);
  server.on("/turkoi", turkoi);
  server.on("/cyan", cyan);
  server.on("/ciel", ciel);
  server.on("/bluewhite", bluewhite);
  server.on("/bluewhite2", bluewhite2);
  server.on("/violetclair", violetclair);
  server.on("/violet", violet);
  server.on("/smooth", smooth);
  server.on("/fade", fade);
  server.on("/strobe", strobe);
  server.on("/flash", flash);
  server.on("/plus", plus);
  server.on("/moin", moin);
  server.on("/on", on);
  server.on("/off", off);


  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();//Handle client requests
  delay(1000);
}
