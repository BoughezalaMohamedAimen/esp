String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String readEssid(){
  Serial.println("Reading EEPROM ssid");

  String esid;
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  }
  Serial.println();
  Serial.print("SSID: ");
  Serial.println(esid);
  return esid;
}

String readPassword(){
  Serial.println("Reading EEPROM pass");

  String epass = "";
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);
  return epass;
}

String readIP(){
  Serial.println("Reading EEPROM ip");

  String eip = "";
  for (int i = 96; i < 111; ++i)
  {
    if(EEPROM.read(i)!=255)
    eip += char(EEPROM.read(i));
  }
  Serial.print("eip: ");
  Serial.println(eip);
  return eip;
}

String readGateway(){
  Serial.println("Reading EEPROM gateway");

  String egateway = "";
  for (int i = 111; i < 126; ++i)
  {
    if(EEPROM.read(i)!=255)
    egateway += char(EEPROM.read(i));
  }
  Serial.print("egateway: ");
  Serial.println(egateway);
  return egateway;
}

String readDns(){
  Serial.println("Reading EEPROM dns");

  String edns = "";
  for (int i = 126; i < 141; ++i)
  {
    if(EEPROM.read(i)!=255)
    edns += char(EEPROM.read(i));
  }
  Serial.print("edns: ");
  Serial.println(edns);
  return edns;
}

String readNetMask(){
  Serial.println("Reading EEPROM netmask");

  String enetmask = "";
  for (int i = 141; i < 156; ++i)
  {
    if(EEPROM.read(i)!=255)
    enetmask += char(EEPROM.read(i));
  }
  Serial.print("enetmask: ");
  Serial.println(enetmask);
  return enetmask;
}

String readDeviceName(){
  Serial.println("Reading EEPROM deviceName");

  String edeviceName = "";
  for (int i = 156; i < 176; ++i)
  {
    if(EEPROM.read(i)!=255)
    edeviceName += char(EEPROM.read(i));
  }
  Serial.print("edeviceName: ");
  Serial.println(edeviceName);
  return edeviceName;
}

void setupAP(){
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(staticIP, gateway, subnet);
  WiFi.softAP(mySsid,myPass);
}

String available_networks()
{
  String av="[]";
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    av="[";
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
      delay(10);
      av+="{\"network\":\""+WiFi.SSID(i)+"\",\"signal\":\""+ WiFi.RSSI(i) +"\"}";
      if(i!=n-1)
      av+=",";
    }
    av+="]";
  }
  return av;
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


//===============================================================================
//          TRYING TO CONNECT TO SSID USING PASS FROM EEPROM
//===============================================================================

void wifiConnect()
{
  //reset networking
  WiFi.softAPdisconnect(true);
  Serial.println("Disconnecting previously connected WiFi");
  WiFi.disconnect();
  delay(1000);

        String _ssid = readEssid();
        String _pass = readPassword();
        String _staticIP=readIP();
        String _gateway=readGateway();
        String _dns=readDns();
        String _subnet=readNetMask();

        if ((_staticIP!="") &&(_gateway!="") &&(_dns!="") &&(_subnet!=""))
        {
          IPAddress new_ip(atoi(getValue(_staticIP, '.', 0).c_str()),atoi(getValue(_staticIP, '.', 1).c_str()),atoi(getValue(_staticIP, '.', 2).c_str()),atoi(getValue(_staticIP, '.', 3).c_str()));
          IPAddress new_gateway(atoi(getValue(_gateway, '.', 0).c_str()),atoi(getValue(_gateway, '.', 1).c_str()),atoi(getValue(_gateway, '.', 2).c_str()),atoi(getValue(_gateway, '.', 3).c_str()));
          IPAddress new_dns(atoi(getValue(_dns, '.', 0).c_str()),atoi(getValue(_dns, '.', 1).c_str()),atoi(getValue(_dns, '.', 2).c_str()),atoi(getValue(_dns, '.', 3).c_str()));
          IPAddress new_subnet(atoi(getValue(_subnet, '.', 0).c_str()),atoi(getValue(_subnet, '.', 1).c_str()),atoi(getValue(_subnet, '.', 2).c_str()),atoi(getValue(_subnet, '.', 3).c_str()));
          WiFi.config(new_ip,new_gateway,new_dns,new_subnet);
        }
//        else
//          WiFi.config(staticIP,gateway,dns,subnet);

        WiFi.mode(WIFI_STA);
        WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)

        WiFi.begin(_ssid, _pass);
        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
          //digitalWrite(pin_led,!digitalRead(pin_led));
          if ((unsigned long)(millis() - startTime) >= 5000) break;
        }
      if (WiFi.status() == WL_CONNECTED)
      {
        Serial.println("connected");
        //digitalWrite(pin_led,HIGH);
      }
      else
      setupAP();
      Serial.println("");
      //WiFi.printDiag(Serial);
}
