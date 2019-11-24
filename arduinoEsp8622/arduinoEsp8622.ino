#include <SoftwareSerial.h>
SoftwareSerial ESPModule(10, 11);//RX, TX
String readstring="";

void setup() {
  ESPModule.begin(9600);
  Serial.begin(9600);
  Serial.println("power up");
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
}

void loop() {
  while (ESPModule.available()) {
    Serial.println("reading");
    delay(3);  //delay to allow buffer to fill
    if (ESPModule.available() >0) {
      char c = ESPModule.read();  //gets one byte from serial buffer
      readstring += c; //makes the string readString
    }
  }

  if (readstring.length() >0)
  {
    if (readstring=="DOOR OPEN"){
       digitalWrite(4,LOW);
      
        delay(1000);
        digitalWrite(4,HIGH);
       
    }
        Serial.println(readstring); //see what was received
     readstring="";  
    }
     
  }
