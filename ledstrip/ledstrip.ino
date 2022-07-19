#include <FastLED.h>

#define NUM_LEDS  40
#define LED_PIN   D4

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);

  
}

void loop() {

  set_color(255,0,0);
  delay(1000);
  set_color(0,0,255);
  set_color(64, 224, 208);
  delay(1000);
  set_color(0,255,0);
  set_color(173, 255, 47);
  delay(1000);
  set_color(255,255,255);
  delay(1000);
  set_color(0,0,0);
  set_color(255, 129, 47);
  
}

void set_color(int red,int green , int blue)
{ 
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(red, green, blue);
    FastLED.show();
    delay(50);
  }

}
