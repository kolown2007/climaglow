#include "config.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

const int ledPin = LED_BUILTIN;
const int bPin = 2;
const char* sunsetAPI_KL = "https://api.sunrise-sunset.org/json?lat=3.1499&lng=101.6945&tzid=Asia/Kuala_Lumpur&formatted=0&date=today";
const char* sunsetAPI_ML = "https://api.sunrise-sunset.org/json?lat=14.5995&lng=120.9842&tzid=Asia/Manila&formatted=0&date=today";
int ledCount = LED_COUNT;

String extractTimeFromISO8601(String iso8601) {
  // Extract the time part from the ISO 8601 string
  int timeStartIndex = iso8601.indexOf('T') + 1;
  int timeEndIndex = iso8601.indexOf('+');
  return iso8601.substring(timeStartIndex, timeEndIndex);
}

void getSunTimes(String &sunriseTime, String &sunsetTime, String &solarNoonTime) {
  HTTPClient http;
  
  http.begin(sunsetAPI_KL);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, payload);
    
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }
    
    sunriseTime = extractTimeFromISO8601(doc["results"]["sunrise"].as<String>());
    sunsetTime = extractTimeFromISO8601(doc["results"]["sunset"].as<String>());
    solarNoonTime = extractTimeFromISO8601(doc["results"]["solar_noon"].as<String>());
  } else {
    Serial.print("HTTP GET request failed with code: ");
    Serial.println(httpCode);
  }
  
  http.end();
}

String computeTime(String startTime, int offsetMinutes) {
  int startHour = startTime.substring(0, 2).toInt();
  int startMinute = startTime.substring(3, 5).toInt();
  int totalMinutes = startHour * 60 + startMinute + offsetMinutes;

  int resultHour = totalMinutes / 60;
  int resultMinute = totalMinutes % 60;

  char buffer[6];
  sprintf(buffer, "%02d:%02d", resultHour, resultMinute);
  return String(buffer);
}

void computeMorningTimes(String sunriseTime, String solarNoonTime, String &earlyMorningTime, String &midMorningTime, String &lateMorningTime) {
  int sunriseHour = sunriseTime.substring(0, 2).toInt();
  int sunriseMinute = sunriseTime.substring(3, 5).toInt();
  int solarNoonHour = solarNoonTime.substring(0, 2).toInt();
  int solarNoonMinute = solarNoonTime.substring(3, 5).toInt();

  int sunriseTotalMinutes = sunriseHour * 60 + sunriseMinute;
  int solarNoonTotalMinutes = solarNoonHour * 60 + solarNoonMinute;

  int interval = solarNoonTotalMinutes - sunriseTotalMinutes;
  int thirdInterval = interval / 3;

  earlyMorningTime = computeTime(sunriseTime, thirdInterval);
  midMorningTime = computeTime(sunriseTime, 2 * thirdInterval);
  lateMorningTime = computeTime(solarNoonTime, -60);
}

void computeAfternoonTimes(String solarNoonTime, String sunsetTime, 
    String &earlyAfternoonTime, String &midAfternoonTime, String &lateAfternoonTime) {
    
    int solarNoonHour = solarNoonTime.substring(0, 2).toInt();
    int solarNoonMinute = solarNoonTime.substring(3, 5).toInt();
    int sunsetHour = sunsetTime.substring(0, 2).toInt();
    int sunsetMinute = sunsetTime.substring(3, 5).toInt();

    int solarNoonTotalMinutes = solarNoonHour * 60 + solarNoonMinute;
    int sunsetTotalMinutes = sunsetHour * 60 + sunsetMinute;

    int interval = sunsetTotalMinutes - solarNoonTotalMinutes;
    int thirdInterval = interval / 3;

    earlyAfternoonTime = computeTime(solarNoonTime, thirdInterval);
    midAfternoonTime = computeTime(solarNoonTime, 2 * thirdInterval);
    lateAfternoonTime = computeTime(sunsetTime, -60); // One hour before sunset
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%H:%M:%S");
  Serial.println(&timeinfo, "%d/%m/%Y   %Z");
}