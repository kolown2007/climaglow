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

  Serial.println("Sunrise time: " + sunriseTime);
  Serial.println("Solar noon: " + solarNoonTime);
  Serial.println("Sunset time: " + sunsetTime);
  Serial.println("Early Morning time: " + earlyMorningTime);
  Serial.println("Mid Morning time: " + midMorningTime);
  Serial.println("Late Morning time: " + lateMorningTime);


  delay(500);
  success(); //red led flash

 
}

void loop() {

  //this is for testing purposes only to see if the colors are changing

  // KLsetSunriseColor();
  // Serial.println("Sunrise color set");
  // delay(10000); 
  // KLsetEarlyMorningColor();
  // Serial.println("Early Morning color set");
  // delay(10000); 
  // KLsetMidMorningColor();
  // Serial.println("Mid Morning color set");
  // delay(10000); 
  // KLsetLateMorningColor();
  // Serial.println("Late Morning color set");
  // delay(10000);
  // KLsetSolarNoonColor();
  // Serial.println("Solar Noon color set");
  // delay(10000);

  // KLsetLateAfternoonColor();
  // delay(5000);
  KLsetSunsetColor();
  // delay(5000);

// struct tm timeinfo;
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
//   } else if (currentTimeStr >= solarNoonTime) {
//     KLsetSolarNoonColor();
//     Serial.println("Solar Noon color set");
//   }

//   delay(60000); // Check every minute


}




