//===============================================================================
//          TRYING TO CONNECT TO SSID USING PASS FROM CONFIG.JSON
//===============================================================================



void wifiSetMode(String mode){
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();

  if(mode=="station")
  {
    WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
    WiFi.config(staticIP,gateway,dns,subnet);
    WiFi.mode(WIFI_STA);
    
  }
  else{
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(staticIP, gateway, subnet);
    WiFi.softAP(mySsid,myPass);
  }
}



void wifiConnect()
{
  if(SPIFFS.exists("/config.json")){
    const char * _ssid = "", *_pass = "";
    File configFile = SPIFFS.open("/config.json", "r");
    if(configFile){
      size_t size = configFile.size();
      std::unique_ptr<char[]> buf(new char[size]);
      configFile.readBytes(buf.get(), size);
      configFile.close();

      DynamicJsonBuffer jsonBuffer;
      JsonObject& jObject = jsonBuffer.parseObject(buf.get());
      if(jObject.success())
      {
        _ssid = jObject["ssid"];
        _pass = jObject["password"];
        wifiSetMode("station");
        WiFi.begin(_ssid, _pass);
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
          //digitalWrite(pin_led,!digitalRead(pin_led));
          if ((unsigned long)(millis() - startTime) >= 5000) break;
        }
      }
    }
  }
}






void wifiInit()
{
  //reset networking
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);
  //check for stored credentials
  wifiConnect();
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("connected");
    //digitalWrite(pin_led,HIGH);
  } else
  {
    wifiSetMode("AP");
    //digitalWrite(pin_led,LOW);
  }
    Serial.println("");
  WiFi.printDiag(Serial);
}








int DoGet(String url){

   http.begin(client,url);
   int httpCode = http.GET();
      if (httpCode > 0)
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
          request_result = http.getString();

      http.end();
      return httpCode;
}
