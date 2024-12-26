#include <Arduino.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "config.h"  
#include "effects.h" 



CRGB leds[LED_COUNT]; // Changed to FastLED
WiFiUDP ntpUDP;
String sunsetTime = "";
String solarNoonTime = "";



void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Ensure this matches the Serial Monitor baud rate


  // Initialize FastLED
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show(); // Turn OFF all pixels

  WiFiManager wm;

  // Configure timeout
  wm.setConfigPortalTimeout(180); // 3 minutes timeout
  
  // Flash LED while waiting for connection
  wm.setAPCallback([](WiFiManager* wm) {
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
  });

  bool res = wm.autoConnect("ClimaGlow", "kolown1234"); //pw: kolown1234

  if(!res) {
    Serial.println("Failed to connect to Wi-Fi. Connect to the configuration portal.");
    digitalWrite(ledPin, HIGH); // LED on indicates error
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("Connected successfully");
    digitalWrite(ledPin, LOW);  // LED off indicates success
  }

  // Configure NTP
  configTime(28800, 0, "pool.ntp.org", "time.nist.gov"); // GMT+8 for Kuala Lumpur and Manila

  // Wait for time to be set
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "Current time: %Y-%m-%d %H:%M:%S");

  // Get and display sunset time
  getSunTimes(sunsetTime, solarNoonTime);
  Serial.println("Sunset time: " + sunsetTime);
  Serial.println("Solar noon: " + solarNoonTime);
}



void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    // Handle WiFi disconnection
    digitalWrite(ledPin, HIGH);
    delay(500);
    
    // Light all LEDs with red
    for(int i = 0; i < LED_COUNT; i++) {
      leds[i] = CRGB::Red;
    }
    FastLED.show();
  } else {
    // Get current time
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
      int currentHour = timeinfo.tm_hour;
      int currentMinute = timeinfo.tm_min;

      // Parse sunset time
      int sunsetHour = sunsetTime.substring(0, 2).toInt();
      int sunsetMinute = sunsetTime.substring(3, 5).toInt();

      // Calculate phase times
      int earlySunsetMinute = sunsetMinute - 30;
      int midSunsetMinute = sunsetMinute - 20;
      int lateSunsetMinute = sunsetMinute - 10;
      int twilightStartMinute = sunsetMinute;
      int twilightEndMinute = sunsetMinute + 10;

      // Adjust for negative minutes
      if (earlySunsetMinute < 0) {
        earlySunsetMinute += 60;
        sunsetHour -= 1;
      }
      if (midSunsetMinute < 0) {
        midSunsetMinute += 60;
        sunsetHour -= 1;
      }
      if (lateSunsetMinute < 0) {
        lateSunsetMinute += 60;
        sunsetHour -= 1;
      }

      // Apply light effects based on time
      if (currentHour >= 1 && currentHour < 9) {
        morningStart();
      } else if (currentHour >= 9 && currentHour < 12) {
        midMorning();
      } else if (currentHour >= 12 && currentHour < 16) {
        afterNoon();
      } else {
        // Check if it's sunset time
        if (currentHour == sunsetHour) {
          if (currentMinute >= earlySunsetMinute && currentMinute < midSunsetMinute) {
            earlySunset();
          } else if (currentMinute >= midSunsetMinute && currentMinute < lateSunsetMinute) {
            midSunset();
          } else if (currentMinute >= lateSunsetMinute && currentMinute < twilightStartMinute) {
            lateSunset();
          } else if (currentMinute >= twilightStartMinute && currentMinute < twilightEndMinute) {
            twilightStart();
          } else if (currentMinute >= twilightEndMinute) {
            twilightEnd();
          }
        }
      }
    }
  }
}



