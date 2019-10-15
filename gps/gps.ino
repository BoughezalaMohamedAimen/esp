

#include <SoftwareSerial.h>

#include <TinyGPS++.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
TinyGPSPlus gps;

SoftwareSerial ss(4,5); // for connect GPS

IPAddress staticIP(192, 168, 1, 33); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask



const char* deviceName = "porte";

String matricule="12345-112-16";
String infotosend="";

//SSID and Password of your WiFi router
const char* ssid = "DJAWEB_BDC44";
const char* password = "C06D8236B7FCA";

float latitude , longitude;

int year,month,date,hour,minute,second;
String date_str,time_str,lat_str,lng_str,str_speed="";

int pm;

int lastsecond=0;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

}

void loop()

{
  getgps();
 // Serial.println("lat_str:"+lat_str+" lng_str: "+lng_str+"str_speed:"+str_speed+"str_time"+time_str+"--str_date:"+date_str);
      }

void getgps()
{
  while (ss.available()>0)
  if(gps.encode(ss.read()))
  {
    if((gps.location.isValid())&&(gps.speed.isValid())&&(gps.date.isValid())&&(gps.time.isValid()))
    {
      /*****************************************GETTING LAT AND LON ******************************************************/
      latitude = gps.location.lat();
      lat_str = String(latitude , 6);
      longitude = gps.location.lng();
      lng_str = String(longitude , 6);



      /*****************************************GETTING SPEED******************************************************/
       str_speed=String(gps.speed.kmph());

       
/*****************************************GETTING DATE******************************************************/
      date_str = "";
      date = gps.date.day();
      month = gps.date.month();
      year = gps.date.year();

      if(year<10)
      date_str += '0';
      date_str += String(year);

      date_str += "-";

      if(month < 10)
      date_str += '0';
      date_str += String(month);

      date_str += "-";
      
      if(date<10)
      date_str = '0';
      date_str += String(date);



      

      

      
      /*****************************************GETTING TIME******************************************************/
      time_str = "";
      hour = gps.time.hour();
      minute = gps.time.minute();
      second = gps.time.second();
      if(hour < 10)
      time_str += '0';
      time_str+=String(hour)+":";
      if(minute < 10)
      time_str += '0';
      time_str+=String(minute)+":";
      if(second < 10)
      time_str += '0';
      time_str+=String(second);

    }

  }


  delay(100);
  lastsecond++;
  if(lastsecond==50)
  {
      if((lat_str!="")&&(lng_str!="")&&(str_speed!="")&&(time_str!=""))
        send();
       lastsecond=0; 
  }

}

void send(){
   HTTPClient http;    //Declare object of class HTTPClient
  infotosend+=lat_str+","+lng_str+","+str_speed+","+date_str+" "+time_str+"*" ;
  //Post Data
  String postData = "mat="+matricule+"&info="+infotosend;
   Serial.println(postData);
  
  http.begin("http://ecole-karisma.com/traceur/voitures/gps/gps");              //Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");   
  
  

  int httpCode = http.POST(postData);   //Send the request
  String payload = http.getString();    //Get the response payload

  if(httpCode==200)
  {
    Serial.println("sent");
   
    Serial.println(payload);
    infotosend="";
  }
  
  Serial.println("code: "); 
  Serial.println(httpCode);
  // Serial.println("info : "+infotosend);
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
}
      
