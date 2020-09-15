//===============================================================
// Server routes
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleToggle1() {
  Serial.println("toggle1");
  digitalWrite(relay1,HIGH);
  delay(500);
 digitalWrite(relay1,LOW);
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle2() {
  Serial.println("toggle2");
  digitalWrite(relay2,HIGH);
  delay(500);
 digitalWrite(relay2,LOW);
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle3() {
  Serial.println("toggle3");
  digitalWrite(relay3,HIGH);
  delay(500);
  digitalWrite(relay3,LOW);
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle4() {
  Serial.println("toggle4");
  digitalWrite(relay4,HIGH);
  delay(500);
  digitalWrite(relay4,LOW);
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle5() {
  Serial.println("toggle5");
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle6() {
  Serial.println("toggle6");
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle7() {
  Serial.println("toggle7");
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
}
void handleToggle8() {
  Serial.println("toggle8");
  server.send(200, "application/json", "{\"status\" : \"ok\"}");
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
