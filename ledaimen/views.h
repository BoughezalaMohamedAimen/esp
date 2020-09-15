//===============================================================
// Server routes
//===============================================================
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void red() {
  irsend.sendNEC(0xFF9867,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void green() {
  irsend.sendNEC(0xFFD827,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void blue() {
  irsend.sendNEC(0xFF8877,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void white() {
  irsend.sendNEC(0xFFA857,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void orangered() {
  irsend.sendNEC(0xFFE817,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void orangeyellow() {
  irsend.sendNEC(0xFF02FD,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void yellow() {
  irsend.sendNEC(0xFF50AF,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void yellowgreen() {
  irsend.sendNEC(0xFF38C7,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void bluegreen() {
  irsend.sendNEC(0xFF48B7,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void turkoi() {
  irsend.sendNEC(0xFF32CD,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void cyan() {
  irsend.sendNEC(0xFF7887,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void ciel() {
  irsend.sendNEC(0xFF28D7,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void bluewhite() {
  irsend.sendNEC(0xFF6897,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void bluewhite2() {
  irsend.sendNEC(0xFF20DF,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void violetclair() {
  irsend.sendNEC(0xFF708F,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void violet() {
  irsend.sendNEC(0xFFF00F,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void smooth() {
  irsend.sendNEC(0xFF30CF,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void fade() {
  irsend.sendNEC(0xFF58A7,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void strobe() {
  irsend.sendNEC(0xFF00FF,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void flash() {
  irsend.sendNEC(0xFFB24D,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}


void plus() {
  irsend.sendNEC(0xFF906F,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void moin() {
  irsend.sendNEC(0xFFB847,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}

void on() {
  irsend.sendNEC(0xFFB04F,32);
 server.send(200, "text/html", MAIN_page); //Send web page
}
void off() {
  irsend.sendNEC(0xFFF807,32);
 server.send(200, "text/html", MAIN_page); //Send web page
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
