


/************************************************************************************************************************************************************************************/
/*                           NETWORK VARRIABLES                       */
/************************************************************************************************************************************************************************************/
IPAddress staticIP(192, 168, 1, 32); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);
char allowed[2][12]={"192.168.1.2","192.168.1.7"};
ESP8266WebServer server(80);
const char* deviceName = "porte";
const char* AP_NAME = "SMARtT-DEVICE";
const char* AP_PASS = "smart@pa5s";



/************************************************************************************************************************************************************************************/
/*                           HARDWARE  VARRIABLES                       */
/************************************************************************************************************************************************************************************/


byte relON[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to serial for open relay
byte relOFF[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay

byte rel2ON[] = {0xA0, 0x02, 0x01, 0xA3};  //Hex command to send to serial for open relay
byte rel2OFF[] = {0xA0, 0x02, 0x00, 0xA2}; //Hex command to send to serial for close relay
