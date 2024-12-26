#include "config.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>



const int ledPin = LED_BUILTIN;
const char* sunsetAPI = "https://api.sunrise-sunset.org/json?lat=3.1499&lng=101.6945&tzid=Asia/Kuala_Lumpur";


void getSunTimes(String &sunsetTime, String &solarNoonTime) {
  HTTPClient http;
  
  http.begin(sunsetAPI);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    StaticJsonDocument<1024> doc;
    deserializeJson(doc, payload);
    sunsetTime = doc["results"]["sunset"].as<String>();
    solarNoonTime = doc["results"]["solar_noon"].as<String>();
   
  }
  
  http.end();
}