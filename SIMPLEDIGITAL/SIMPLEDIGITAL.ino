#include <ESP8266WiFi.h>
#define LED D2

void setup() {
// initialize digital pin 16 as an output.
Serial.begin(115200);
pinMode(D2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
   for(int i=0; i<255; i++){
    analogWrite(D2, i);
    delay(15);
  }
  for(int i=255; i<=0; i--){
    analogWrite(D2, i);
    delay(15);
  }
}
