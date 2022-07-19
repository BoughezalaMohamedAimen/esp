#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include <stdlib.h>
#include "global_variables.h"
#include "templates.h"
#include "functions.h"
#include "views.h"








void setup()
{

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor

  FastLED.addLeds<WS2812B, D4, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  
  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);

  Serial.println();
  Serial.println();
  Serial.println("Startup");
  set_color(255,255,255);
 wifiConnect();
//  //---------------------------------------- Read EEPROM for SSID and pass
 server.on("/changeSettings",changeSettings);
 server.on("/scan",handlescan);
 server.on("/settings", HTTP_POST, handleSettingsUpdate);
 server.on("/settings/ip", HTTP_POST, handleIP );
 server.on("/info", handleInfo);
 server.on("/ap", access_point_on);
 server.on("/color", handleColor);
 server.on("/animation", handleAnimation);
 server.on("/", handleRoot);


 server.begin();
}
void loop() {
  server.handleClient();
  delay(500);
}
