//===============================================================
// Server routes
//===============================================================
void handleRoot() {
 server.send(200, "text/html",MAIN_page); //Send web page
}


void handleOn() {
 server.send(200, "text/html",MAIN_page); //Send web page
 digitalWrite(relay,HIGH);

}


void handleOff() {
 server.send(200, "text/html",MAIN_page); //Send web page
 digitalWrite(relay,LOW);
}










//===============================================================================
//          CHANGING  SSID AND PASS IN CONFIG.JSON
//===============================================================================

void handleSettingsUpdate()
{
  String data = server.arg("plain");
  Serial.println(data);
  DynamicJsonBuffer jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);

  File configFile = SPIFFS.open("/config.json", "w");
  jObject.printTo(configFile);
  configFile.close();

  server.send(200, "application/json", "{\"status\" : \"ok\"}");
  delay(500);

  wifiInit();
}


void changeSettings(){
  server.send(200,"text/html", settingsPage);
}
