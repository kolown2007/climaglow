#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <NTPClient.h>

#define LED_PIN    13  // NeoPixel data pin
#define LED_COUNT   8  // Number of LEDs
#define BRIGHTNESS 50  // Set brightness (0-255)

extern const int ledPin;
extern const char* sunsetAPI;

void getSunTimes(String &sunsetTime, String &solarNoonTime);

#endif