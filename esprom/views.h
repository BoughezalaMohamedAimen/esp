//===============================================================
// Server routes
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handlescan(){
  String networks= available_networks();
  server.send(200, "application/json", networks);
}

void handleInfo(){
  String json="{\"ip\":\""+WiFi.localIP().toString()+"\",\"name\":\""+deviceName+"\",";

  json+="\"routes\":[";
  json+="{\"path\":\"one\",\"name\":\"relay 1\"}";
  json+="]}";
  server.send(200,"application/json",json);
}

void handleIP(){
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, server.arg("plain"));

  String new_ip = doc["ip"];
  String new_gateway = doc["gateway"];
  String new_dns = doc["dns"];
  String new_netmask = doc["netmask"];
  String new_device_name=doc["device_name"];

  Serial.println("new ip :"+new_ip);
  Serial.println("new_gateway :"+new_gateway);
  Serial.println("new_dns :"+new_dns);
  Serial.println("new_netmask:"+new_netmask);
  Serial.println("new_device_name:"+new_device_name);
  
  for (int i = 96; i < 156; ++i)   // CLEARING EEPROM NETWORK CONFIG
    EEPROM.write(i, 0);

  for (int i = 0; i < new_ip.length(); ++i)   // WRITING IP INTO EEPROM
    EEPROM.write(96+i, new_ip[i]);

  for (int i = 0; i < new_gateway.length(); ++i)   // WRITING GATEWAY INTO EEPROM
    EEPROM.write(i+111, new_gateway[i]);

  for (int i = 0; i < new_dns.length(); ++i)   // WRITING DNS INTO EEPROM
    EEPROM.write(i+126, new_dns[i]);

  for (int i = 0; i < new_netmask.length(); ++i)   // WRITING NETWORK MASK  INTO EEPROM
    EEPROM.write(i+141, new_netmask[i]);

  for (int i = 0; i < new_device_name.length(); ++i)   // WRITING NETWORK MASK  INTO EEPROM
    EEPROM.write(i+156, new_device_name[i]);

  EEPROM.commit();
  server.send(200, "application/json", "{ \"status\":\"ok\"}");

  delay(500);

  wifiConnect();

}

void access_point_on(){
   server.send(200, "application/json", "{ \"status\":\"ok\"}");
   setupAP();
}
//===============================================================================
//          CHANGING  SSID AND PASS IN EEPROM
//===============================================================================

void handleSettingsUpdate()
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, server.arg("plain"));
  Serial.println(server.arg("plain"));

  String qsid = doc["ssid"];  //READING JSON FROM POST REQUEST
  String qpass = doc["password"];
  if (qsid.length() > 0 && qpass.length() > 0) {
    Serial.println("clearing eeprom");
    for (int i = 0; i < 96; ++i) // CLEARING EEPROM
      EEPROM.write(i, 0);

    Serial.println(qsid);
    Serial.println("");
    Serial.println(qpass);
    Serial.println("");

    Serial.println("writing eeprom ssid:");
    for (int i = 0; i < qsid.length(); ++i) //WRITTING SSID INTO EEPROM
    {
      EEPROM.write(i, qsid[i]);
      Serial.print("Wrote: ");
      Serial.println(qsid[i]);
    }
    Serial.println("writing eeprom pass:");
    for (int i = 0; i < qpass.length(); ++i) //WRITTING PASSWORD INTO EEPROM
    {
      EEPROM.write(32 + i, qpass[i]);
      Serial.print("Wrote: ");
      Serial.println(qpass[i]);
    }
    EEPROM.commit();

    content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
    statusCode = 200;
  } else {
    content = "{\"Error\":\"404 not found\"}";
    statusCode = 404;
    Serial.println("Sending 404");
  }
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(statusCode, "application/json", content);
  delay(500);

  wifiConnect();
}


void changeSettings(){
  server.send(200,"text/html", settingsPage);
}
