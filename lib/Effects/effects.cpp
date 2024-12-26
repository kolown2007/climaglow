#include "effects.h"

extern CRGB leds[]; // Declare the external LED array

void morningStart() {
  static bool pulseUp = true;
  static uint8_t brightness = 0;
  if (pulseUp) {
    brightness++;
    if (brightness >= 255) pulseUp = false;
  } else {
    brightness--;
    if (brightness <= 0) pulseUp = true;
  }
  fill_solid(leds, LED_COUNT, CRGB(255, 248, 220).nscale8(brightness));
  FastLED.show();
  delay(100); // Adjust for smoother pulsing
}

void midMorning() {
  fill_solid(leds, LED_COUNT, CRGB(224, 255, 255));
  FastLED.show();
}

void daylightFade() {
  fill_solid(leds, LED_COUNT, CRGB(200, 230, 255));
  FastLED.show();
}

void afterNoon() {
  fill_solid(leds, LED_COUNT, CRGB(200, 230, 255));
  FastLED.show();
}

void earlySunset() {
  fill_solid(leds, LED_COUNT, CRGB(245, 245, 200));
  FastLED.show();
}

void midSunset() {
  fill_solid(leds, LED_COUNT, CRGB(220, 180, 160));
  FastLED.show();
}

void lateSunset() {
  fill_solid(leds, LED_COUNT, CRGB(200, 140, 180));
  FastLED.show();
}

void twilightStart() {
  fill_solid(leds, LED_COUNT, CRGB(140, 90, 160));
  FastLED.show();
}

void twilightEnd() {
  fill_solid(leds, LED_COUNT, CRGB(80, 60, 120));
  FastLED.show();
}