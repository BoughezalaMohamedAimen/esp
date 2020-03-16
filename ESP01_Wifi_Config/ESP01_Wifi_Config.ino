#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "global_variables.h"
#include "templates.h"
#include "functions.h"
#include "views.h"


//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  delay(500);
  EEPROM.begin(512); //Initialasing EEPROM
    delay(10);
  wifiConnect();
  delay(500);
  server.on("/config",SettingsForm);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/", handleRoot);
  server.on("/open", handleOuvrir);
  server.begin();


}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();//Handle client requests
  delay(1000);
}
