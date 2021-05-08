//===============================================================
// Server routes
//===============================================================
void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}


void handleUp() {
 server.send(200, "text/html",MAIN_page); //Send web page
 
 digitalWrite(down,LOW);
 delay(1000);
 digitalWrite(up,HIGH);
}

void handlePause() {
 server.send(200, "text/html",MAIN_page); //Send web page
 digitalWrite(up,LOW);
 delay(500);
 digitalWrite(down,LOW);
}

void handleDown() {
 
 server.send(200, "text/html",MAIN_page); //Send web page
 digitalWrite(up,LOW);
 delay(1000);
 digitalWrite(down,HIGH);
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
