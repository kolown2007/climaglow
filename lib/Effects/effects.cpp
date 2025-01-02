#include "effects.h"

extern CRGB leds[]; // Declare the external LED array


//utility effects

void success() {
   digitalWrite(ledPin, HIGH);
   delay(500);
    digitalWrite(ledPin, LOW);
}


void wifiConnected(){
  fill_solid(leds, LED_COUNT, CRGB(255, 0, 0));
  FastLED.show();
}

// light effects

//KL lights

void KLsetSunriseColor() {
    // fill_solid(leds, LED_COUNT, CRGB(255, 248, 220)); // Soft Creamy White
fill_rainbow(leds, LED_COUNT, 255/LED_COUNT);
    FastLED.show();
}

void KLsetEarlyMorningColor() {
   // fill_solid(leds, LED_COUNT, CRGB(245, 235, 200)); // Pale Yellow
       fill_solid(leds, LED_COUNT, CRGB::RoyalBlue); 
    FastLED.show();
}

void KLsetMidMorningColor() {
    //fill_solid(leds, LED_COUNT, CRGB(224, 255, 255)); // Cool Blue-White
      fill_solid(leds, LED_COUNT, CRGB::Maroon); 
    FastLED.show();
}

void KLsetLateMorningColor() {
    //fill_solid(leds, LED_COUNT, CRGB(200, 230, 255)); // Subtle Sky Blue
      fill_gradient_RGB(leds, LED_COUNT, CRGB::Green, CRGB::Blue);
    FastLED.show();
}

void KLsetSolarNoonColor() {
    //fill_solid(leds, LED_COUNT, CRGB(180, 230, 255)); // Vibrant Sky Blue
     fill_gradient_RGB(leds, LED_COUNT, CRGB::Red, CRGB::Green);
    FastLED.show();
}

void KLsetEarlyAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 225, 204)); // Soft Peach
    FastLED.show();
}

void KLsetMidAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 200, 170)); // Warm Coral
    FastLED.show();
}

void KLsetLateAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 183, 153)); // Soft Peach transitioning to Gentle Pink
    FastLED.show();
}

void KLsetSunsetColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 102, 178)); // Soft Peach transitioning to Gentle Pink
    FastLED.show();
}

// Manila lights

void MLsetSunriseColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 223, 186)); // Warm Yellow
    FastLED.show();
}

void MLsetEarlyMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 245, 210)); // Soft Warm Cream
    FastLED.show();
}

void MLsetMidMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 255, 204)); // Light Yellow
    FastLED.show();
}

void MLsetLateMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(240, 255, 240)); // Mint Green
    FastLED.show();
}

void MLsetSolarNoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(224, 255, 255)); // Cool Blue-White
    FastLED.show();
}

void MLsetEarlyAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(200, 240, 255)); // Sky Blue
    FastLED.show();
}

void MLsetMidAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 230, 200)); // Warm Peach
    FastLED.show();
}

void MLsetLateAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 200, 150)); // Golden Orange
    FastLED.show();
}

void MLsetSunsetColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 102, 0)); // Bright Orange transitioning to Deep Red
    FastLED.show();
}






