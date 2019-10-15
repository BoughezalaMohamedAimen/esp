
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

TinyGPSPlus gps;

SoftwareSerial ss(4,5); // for connect GPS

IPAddress staticIP(192, 168, 1, 33); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask



const char* deviceName = "porte";



//SSID and Password of your WiFi router
const char* ssid = "DJAWEB_BDC44";
const char* password = "C06D8236B7FCA";

float latitude , longitude;

int year,month,date,hour,minute,second;
String date_str,time_str,lat_str,lng_str,str_speed="";

int pm;

WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 WiFi.begin(ssid, password);     //Connect to your WiFi router

  //Onboard LED port Direction output


  WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration

  WiFi.hostname(deviceName);      // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway);
  WiFi.begin(ssid, password);

  WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
  Serial.println("Start Started");

  //Show IP address

  Serial.println(WiFi.localIP());

}

void loop()

{
  while (ss.available()>0)
  if(gps.encode(ss.read()))
  {
    if(gps.location.isValid())
    {
      latitude = gps.location.lat();
      lat_str = String(latitude , 6);
      longitude = gps.location.lng();
      lng_str = String(longitude , 6);


    }
  if(gps.speed.isValid())
  str_speed=String(gps.speed.kmph());
    if(gps.date.isValid())

    {
      date_str = "";
      date = gps.date.day();
      month = gps.date.month();
      year = gps.date.year();

      if(date<10)
      date_str = '0';
      date_str += String(date);

      date_str += "/";

      if(month < 10)
      date_str += '0';
      date_str += String(month);

      date_str += "/";

      if(year<10)
      date_str += '0';
      date_str += String(year);
    }

    if(gps.time.isValid())
    {
      time_str = "";
      hour = gps.time.hour();
      minute = gps.time.minute();
      second = gps.time.second();

      minute = (minute + 30);
      if(minute>59)
      {
        minute = minute - 60;
        hour = hour + 1;
      }
      hour = (hour + 5);
      if (hour > 23)
      hour = hour - 24;

      if(hour>= 12)
      pm = 1;

      else

      pm = 0;

      hour = hour % 12;

      if(hour < 10)
     time_str ='0';
     time_str += String(hour);

     time_str += ":";

     if(minute<10)
     time_str ='0';
     time_str += String(minute);

     time_str += ":";

     if(second<10)
     time_str ='0';
     time_str += String(second);

     if (pm == 1)
     time_str += "PM";
     else
     time_str += "AM";

    }

  }

  // Check if a client has connected

  WiFiClient client = server.available();
  if(!client)
  {
    return;

  }

  //prepare the response

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html><html><head><title>GPSNodeMCU A-Arduino </title><style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table,th,td {border: 1px solid black;}</style></head><body><h1 style=";
  s += "font-size:300%;";
  s += " ALIGN=CENTER> GPS Interfacing with NodeMCU</h1>";
  s += "<p ALIGN=CENTER style=""font-size:150%;""";
  s += "> <b>Location Details</b></p><table ALIGN=CENTER style=";
  s += "width:50%";
  s += "> <tr> <th>Latitude</th>";
  s += "<td ALIGN=CENTER>";
  s += lat_str;
  s += "</td></tr><tr><th>Longitude</th><td ALIGN=CENTER>";
  s += lng_str;
  s += "</td></tr><tr><th>Date</th><td ALIGN=CENTER>";
  s += date_str;
  s += "</td></tr><tr><th>Time</th><td ALIGN=CENTER>";
  s += time_str+"speed:"+str_speed;
  s += "</td></tr></table>";

  if(gps.location.isValid())
  {
   s += "<a href=\"http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
   s += lat_str;
   s += '+';
   s += lng_str;
   s += "\">Click here!To check the location in Google maps.</a>";
  }

   s += "</body> </html> \n";

  client.print(s);
  delay(100);


      }
