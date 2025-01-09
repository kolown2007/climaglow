#include <Arduino.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FastLED.h>
#include "config.h"  
#include "effects.h" 

CRGB leds[LED_COUNT]; 

String sunriseTime = "";
String sunsetTime = "";
String solarNoonTime = "";
String earlyMorningTime = "";
String midMorningTime = "";
String lateMorningTime = "";
String earlyAfternoonTime = "";
String midAfternoonTime = "";
String lateAfternoonTime = "";
String nightTime = "";



void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); //  baud rate that works in vscode

  // Initialize FastLED
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  WiFiManager wm;

  // Configure timeout
  wm.setConfigPortalTimeout(180); // 3 minutes timeout
  
  // Flash LED while waiting for connection
  wm.setAPCallback([](WiFiManager* wm) {
    success(); //red led flash
  });

  bool res = wm.autoConnect("ClimaGlow", "kolown1234"); //pw: kolown1234

  if(!res) {
    Serial.println("Failed to connect to Wi-Fi. Connect to the configuration portal.");
    digitalWrite(bPin, HIGH); // LED on indicates error
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("Connected successfully");
    digitalWrite(ledPin, LOW);  // LED off indicates success
  }
 

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    digitalWrite(bPin, HIGH); // LED on indicates error
    return;
  } else {
    success(); //red led flash
    Serial.println("NTP time synchronized successfully");
    Serial.println(&timeinfo, "Current time: %Y-%m-%d %H:%M:%S");
  }

  // Get and display sunset time
  getSunTimes(sunriseTime, sunsetTime, solarNoonTime);
  delay(500);
  computeMorningTimes(sunriseTime, solarNoonTime, earlyMorningTime, midMorningTime, lateMorningTime);
  computeAfternoonTimes(solarNoonTime, sunsetTime, earlyAfternoonTime, midAfternoonTime, lateAfternoonTime, nightTime);

  Serial.println("Sunrise time: " + sunriseTime);
  Serial.println("Solar noon: " + solarNoonTime);
  Serial.println("Sunset time: " + sunsetTime);
  Serial.println("Early Morning time: " + earlyMorningTime);
  Serial.println("Mid Morning time: " + midMorningTime);
  Serial.println("Late Morning time: " + lateMorningTime);
  Serial.println("Early Afternoon time: " + earlyAfternoonTime);
  Serial.println("Mid Afternoon time: " + midAfternoonTime);
  Serial.println("Late Afternoon time: " + lateAfternoonTime);
  Serial.println("Night time: " + nightTime);


  delay(500);
  success(); //red led flash

 
}

void loop() {

  // for KLSetUp
//  struct tm timeinfo;
//   if (!getLocalTime(&timeinfo)) {
//     Serial.println("Failed to obtain time");
//     return;
//   }

//   char currentTime[6];
//   strftime(currentTime, sizeof(currentTime), "%H:%M", &timeinfo);
//   String currentTimeStr = String(currentTime);

//   if (currentTimeStr >= sunriseTime && currentTimeStr < earlyMorningTime) {
//     KLsetSunriseColor();
//     Serial.println("Sunrise color set");
//   } else if (currentTimeStr >= earlyMorningTime && currentTimeStr < midMorningTime) {
//     KLsetEarlyMorningColor();
//     Serial.println("Early Morning color set");
//   } else if (currentTimeStr >= midMorningTime && currentTimeStr < lateMorningTime) {
//     KLsetMidMorningColor();
//     Serial.println("Mid Morning color set");
//   } else if (currentTimeStr >= lateMorningTime && currentTimeStr < solarNoonTime) {
//     KLsetLateMorningColor();
//     Serial.println("Late Morning color set");
//   } else if (currentTimeStr >= solarNoonTime && currentTimeStr < earlyAfternoonTime) {
//     KLsetSolarNoonColor();
//     Serial.println("Solar Noon color set");
//   } else if (currentTimeStr >= earlyAfternoonTime && currentTimeStr < midAfternoonTime) {
//     KLsetEarlyAfternoonColor();
//     Serial.println("Early Afternoon color set");
//   } else if (currentTimeStr >= midAfternoonTime && currentTimeStr < lateAfternoonTime) {
//     KLsetMidAfternoonColor();
//     Serial.println("Mid Afternoon color set");
//   } else if (currentTimeStr >= lateAfternoonTime && currentTimeStr < sunsetTime) {
//     KLsetLateAfternoonColor();
//     Serial.println("Late Afternoon color set");
//   } else if (currentTimeStr >= sunsetTime && currentTimeStr < nightTime) {
//     KLsetSunsetColor();
//     Serial.println("Sunset color set");
//   } else if (currentTimeStr >= nightTime || currentTimeStr < sunriseTime) {
//     NightLights();
//     Serial.println("Night color set");
//   }

//   delay(60000); // Check every minute





// for MLSetUp
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  char currentTime[6];
  strftime(currentTime, sizeof(currentTime), "%H:%M", &timeinfo);
  String currentTimeStr = String(currentTime);

  if (currentTimeStr >= sunriseTime && currentTimeStr < earlyMorningTime) {
    MLsetSunriseColor();
    Serial.println("Sunrise color set");
  } else if (currentTimeStr >= earlyMorningTime && currentTimeStr < midMorningTime) {
    MLsetEarlyMorningColor();
    Serial.println("Early Morning color set");
  } else if (currentTimeStr >= midMorningTime && currentTimeStr < lateMorningTime) {
    MLsetMidMorningColor();
    Serial.println("Mid Morning color set");
  } else if (currentTimeStr >= lateMorningTime && currentTimeStr < solarNoonTime) {
    MLsetLateMorningColor();
    Serial.println("Late Morning color set");
  } else if (currentTimeStr >= solarNoonTime && currentTimeStr < earlyAfternoonTime) {
    MLsetSolarNoonColor();
    Serial.println("Solar Noon color set");
  } else if (currentTimeStr >= earlyAfternoonTime && currentTimeStr < midAfternoonTime) {
    MLsetEarlyAfternoonColor();
    Serial.println("Early Afternoon color set");
  } else if (currentTimeStr >= midAfternoonTime && currentTimeStr < lateAfternoonTime) {
    MLsetMidAfternoonColor();
    Serial.println("Mid Afternoon color set");
  } else if (currentTimeStr >= lateAfternoonTime && currentTimeStr < sunsetTime) {
    MLsetLateAfternoonColor();
    Serial.println("Late Afternoon color set");
  } else if (currentTimeStr >= sunsetTime && currentTimeStr < nightTime) {
    MLsetSunsetColor();
    Serial.println("Sunset color set");
  } else if (currentTimeStr >= nightTime || currentTimeStr < sunriseTime) {
    NightLights();
    Serial.println("Night color set");
  }

  delay(60000); // Check every minute

}







