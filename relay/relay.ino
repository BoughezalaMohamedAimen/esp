
/*
 * ESP8266 NodeMCU LED Control over WiFi Demo
 * Using Static IP Address for ESP8266
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>



byte relON[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to serial for open relay
byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay
//
// byte rel2ON[] = {0xA0, 0x02, 0x01, 0xA3};  //Hex command to send to serial for open relay
// byte rel2OFF[] = {0xA0, 0x02, 0x00, 0xA2}; //Hex command to send to serial for close relay

//---------------------------------------------------------------
//Our HTML webpage contents in program memory
const char * MAIN_page= "<!DOCTYPE html>"
"<html lang='fr'>"
"<head>"
  "<meta charset='UTF-8'>"
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
"</head>"
"<body>"
"<style>"
"body{"
"margin: 0;"
"width: 100%;"
"height: 100vh;"
"font-family: 'Exo', sans-serif;"
"color: #fff;"
"background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);"
"background-size: 400% 400%;"
"animation: gradientBG 15s ease infinite;"
"}"
"@keyframes gradientBG {"
"  0% {background-position: 0% 50%;}50% {background-position: 100% 50%;}100% {background-position: 0% 50%;}}"
".center-fixed { position: fixed !important;}"
".center {"
  "position: absolute;"
  "left: 50%;"
  "top: 50%;"
  "-webkit-transform: translate(-50%,-50%);"
  "-ms-transform: translate(-50%,-50%);"
  "transform: translate(-50%,-50%);"
  "text-align: center;"
"}"
".button--moema {padding: 1.5em 3em;border-radius: 50px;background: #7986cb;color: #fff;-webkit-transition: background-color 0.3s, color 0.3s;transition: background-color 0.3s, color 0.3s;}"
".button--moema.button--inverted {background: transparent;color: #fff;border:1px solid whitesmoke;}"
".button--moema::before {content: '';position: absolute;top: -20px;left: -20px;bottom: -20px;right: -20px;background: inherit;"
"border-radius: 50px;z-index: -1;opacity: 0.4;-webkit-transform: scale3d(0.8, 0.5, 1);transform: scale3d(0.8, 0.5, 1);}"
".button--moema:hover {-webkit-transition: background-color 0.1s 0.3s, color 0.1s 0.3s;"
" transition: background-color 0.1s 0.3s, color 0.1s 0.3s;color: #ECEFF1;background-color: #3f51b5;-webkit-animation: anim-moema-1 0.3s forwards;animation: anim-moema-1 0.3s forwards;}"
".button--moema.button--inverted:hover {color: #fff;background-color: transparent;}"
".button--moema:hover::before {-webkit-animation: anim-moema-2 0.3s 0.3s forwards;animation: anim-moema-2 0.3s 0.3s forwards;}"
"@-webkit-keyframes anim-moema-1 {60% {-webkit-transform: scale3d(0.8, 0.8, 1);transform: scale3d(0.8, 0.8, 1);}85% {-webkit-transform: scale3d(1.1, 1.1, 1);transform: scale3d(1.1, 1.1, 1);}100% {-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"@keyframes anim-moema-1 {60% {-webkit-transform: scale3d(0.8, 0.8, 1);transform: scale3d(0.8, 0.8, 1);}"
" 85% {-webkit-transform: scale3d(1.1, 1.1, 1);transform: scale3d(1.1, 1.1, 1);}100% {-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"@-webkit-keyframes anim-moema-2 {to {opacity: 0;-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"@keyframes anim-moema-2 {  to {opacity: 0;-webkit-transform: scale3d(1, 1, 1);transform: scale3d(1, 1, 1);}}"
"a{color:inherit !important;text-decoration: none !important;}"
"</style>"
"<div class='center center-fixed'>"
"<button  class='button button--moema button--inverted button--text-thick button--size-s'><a href='http://192.168.1.30/open'>Ouvrir Porte</a></button>"
"</div>"
"</body>"
"</html>";
//---------------------------------------------------------------


//Static IP address configuration
IPAddress staticIP(192, 168, 1, 30); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask



const char* deviceName = "porte";



//SSID and Password of your WiFi router
const char* ssid = "DJAWEB_BDC44";
const char* password = "C06D8236B7FCA";

//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleOuvrir() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page

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



//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  
  
  //digitalWrite(5,LOW);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
 Serial.print(ssid); Serial.println(" ...");

  //Onboard LED port Direction output


  WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration

  WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway);
  WiFi.begin(ssid, password);



  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
     

  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/open", handleOuvrir); //as Per  <a href="ledOn">, Subroutine to be called

  server.begin();                  //Start server
  
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();//Handle client requests
  delay(500);
}
