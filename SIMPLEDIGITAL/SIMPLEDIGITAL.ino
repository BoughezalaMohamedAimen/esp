void setup() {
// initialize digital pin 16 as an output.
//Serial.begin(115200);
    pinMode(2, OUTPUT);
delay(1000);
}

// the loop function runs over and over again forever
void loop() {

    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(2000);

  
}
