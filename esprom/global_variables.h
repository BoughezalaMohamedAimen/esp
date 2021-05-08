//Static IP address configuration
IPAddress staticIP(192, 168, 1, 40); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress dns(192, 168, 1, 1);  //Subnet mask
IPAddress subnet(255, 255, 255, 0);  //Subnet mask

const char* deviceName = "Blue device";
char* mySsid = "esp8266 by aimen";
char* myPass = "123456789";

String request_result;

//SSID and Password of your WiFi router

// char allowed[2][12]={"192.168.1.2","192.168.1.7"};
//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80

WiFiClient client;

HTTPClient http;

int i = 0;
int statusCode;
String content;
