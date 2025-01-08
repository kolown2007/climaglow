#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#define LED_PIN    13  // NeoPixel data pin
#define LED_COUNT   600  // Number of LEDs
#define BRIGHTNESS 255  // Set brightness (0-255)

#define NTP_SERVER     "time3.google.com"
#define UTC_OFFSET     28800
#define UTC_OFFSET_DST 0

extern const int ledPin;
extern const int bPin;
extern const char* sunsetAPI;

void getSunTimes(String &sunriseTime, String &sunsetTime, String &solarNoonTime);
void printLocalTime();
void computeMorningTimes(String sunriseTime, String solarNoonTime, String &earlyMorningTime, String &midMorningTime, String &lateMorningTime);
void computeAfternoonTimes(String solarNoonTime, String sunsetTime, String &earlyAfternoonTime, String &midAfternoonTime, String &lateAfternoonTime, String &nightTime);
#endif