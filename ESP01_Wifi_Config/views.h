void handleRoot() {
 server.send(200, "text/html", MAIN_page); //Send web page
}


//===============================================================================
//          OPENING THE DOOR
//===============================================================================

void handleOuvrir() {
 // String s = "  <br><h1>local</h1>"+server.client().localIP().toString()+"  <br><h1>remote</h1>"+ server.client().remoteIP().toString();
 // if(in_allowed(server.client().remoteIP().toString()))
 //   s = "  <br><h1>allowed Mac</h1>"+server.client().remoteIP().toString();
// Serial.println("client info:");
// Serial.println(server.client());
/*Serial.print(server.client().bssid()[1],HEX);
Serial.print(server.client().bssid()[2],HEX);
Serial.print(server.client().bssid()[3],HEX);
Serial.print(server.client().bssid()[4],HEX);
Serial.print(server.client().bssid()[5],HEX);*/
// String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", MAIN_page); //Send web page
 Serial.begin(115200);
 Serial.flush();
 delay(500);
 Serial.write(relON, sizeof(relON));
 delay(1000);

 //turn the relay off for 3 seconds
 Serial.write(relOFF, sizeof(relOFF));
 delay(1000);

 Serial.end();

}



//===============================================================================
//          CHANGING  SSID AND PASS IN CONFIG.JSON
//===============================================================================

void handleSettingsUpdate()
{
  String data = server.arg("plain");
  //Serial.println(data);
  DynamicJsonBuffer jBuffer;
  JsonObject& jObject = jBuffer.parseObject(data);

  File configFile = SPIFFS.open("/config.json", "w");
  jObject.printTo(configFile);
  configFile.close();

  server.send(200, "application/json", "{\"status\" : \"ok\"}");
  delay(1000);

  wifiConnect();
}


void SettingsForm(){
  server.send(200,"text/html", SETTINGS_PAGE);
}
