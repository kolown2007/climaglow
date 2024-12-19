#include <Arduino.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FastLED.h> // Changed to FastLED

const int ledPin = LED_BUILTIN;
const char* sunsetAPI = "https://api.sunrise-sunset.org/json?lat=3.1499&lng=101.6945&tzid=Asia/Kuala_Lumpur";
#define LED_PIN    13  // NeoPixel data pin
#define LED_COUNT  12  // Number of LEDs
#define BRIGHTNESS 50  // Set brightness (0-255)

CRGB leds[LED_COUNT]; // Changed to FastLED

String getSunsetTime() {
  HTTPClient http;
  String sunsetTime = "";
  
  http.begin(sunsetAPI);
  int httpCode = http.GET();
  
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    sunsetTime = doc["results"]["sunset"].as<String>();
    Serial.println("Sunset time: " + sunsetTime);
  }
  
  http.end();
  return sunsetTime;
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

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

  bool res = wm.autoConnect("ClimaGlow", "kolown"); // SSID and password for AP mode

  if(!res) {
    Serial.println("Failed to connect");
    digitalWrite(ledPin, HIGH); // LED on indicates error
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("Connected successfully");
    digitalWrite(ledPin, LOW);  // LED off indicates success
  }
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    // Handle WiFi disconnection
    digitalWrite(ledPin, HIGH);
    
    delay(500);
  }
}