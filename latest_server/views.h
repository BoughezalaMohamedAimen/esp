//===============================================================
// Server routes
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
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

  wifiConnect();
}


void changeSettings(){
  server.send(200,"text/html", settingsPage);
}
