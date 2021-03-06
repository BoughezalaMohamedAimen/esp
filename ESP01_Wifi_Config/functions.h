
//===============================================================================
//          TRYING TO CONNECT TO SSID USING PASS FROM CONFIG.JSON
//===============================================================================

void wifiConnect()
{
  //reset networking
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  delay(1000);
  //check for stored credentials
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
        WiFi.mode(WIFI_STA);
       // WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
        WiFi.config(staticIP, gateway, subnet);
        WiFi.begin(_ssid, _pass);
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          //Serial.print(".");
          //digitalWrite(pin_led,!digitalRead(pin_led));
          if ((unsigned long)(millis() - startTime) >= 5000) break;
        }
      }
    }
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    //Serial.println("connected");
    //digitalWrite(pin_led,HIGH);
  } else
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(staticIP, gateway, subnet);
    WiFi.softAP(AP_NAME, AP_PASS);
    //digitalWrite(pin_led,LOW);
  }
    //Serial.println("");
  WiFi.printDiag(Serial);
}
//===============================================================
// Finding and validating ip adresses
//===============================================================
boolean in_allowed(String element)
{
  for (int i = 0; i < sizeof(allowed); i++)
  {
    //Serial.println(allowed[i]);
    if ((String)allowed[i] == element)
      return true;
  }
  return false;
}
