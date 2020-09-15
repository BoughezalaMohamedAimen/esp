//Static IP address configuration
IPAddress staticIP(192, 168, 1, 40); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask

const char* deviceName = "SMART-DEVICE";
char* mySsid = "SMART-DEVICE";
char* myPass="123456789";


//SSID and Password of your WiFi router

// char allowed[2][12]={"192.168.1.2","192.168.1.7"};
//Declare a global object variable from the ESP8266WebServer class.
ESP8266WebServer server(80); //Server on port 80


/************************************************************************************************************************************************************************************/
/*                           HARDWARE  VARRIABLES                       */
/************************************************************************************************************************************************************************************/



#define relay1 D0 
#define relay2 D6
#define relay3 D7
#define relay4 D5
