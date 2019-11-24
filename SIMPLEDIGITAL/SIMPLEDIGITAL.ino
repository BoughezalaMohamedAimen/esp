#include <ESP8266WiFi.h>
#define LED D2

void setup() {
// initialize digital pin 16 as an output.
Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  delay(2000);
  pinMode(LED, OUTPUT);
delay(2000);
pinMode(LED, INPUT);
}
