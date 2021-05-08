#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

#include "global_variables.h"
#include "templates.h"
#include "functions.h"
#include "views.h"




void setup()
{

  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor

  EEPROM.begin(512); //Initialasing EEPROM
  delay(10);
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.println();
  Serial.println("Startup");
  wifiConnect();
  //---------------------------------------- Read EEPROM for SSID and pass
  server.on("/changeSettings",changeSettings);
  server.on("/scan",handlescan);
  server.on("/settings", HTTP_POST, handleSettingsUpdate);
  server.on("/settings/ip", HTTP_POST, handleIP );
  server.on("/info", handleInfo);
  server.on("/ap", access_point_on);
  server.on("/", handleRoot);


  server.begin();
}
void loop() {
  server.handleClient();
  delay(500);

}
