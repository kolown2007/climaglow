#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <RGBLed.h>
#include <Arduino_JSON.h>

//wifi setup
const char* ssid = "";
const char* password = "";

// dont share the API key
String openWeatherMapApiKey = "d703826ebc06e58937f0e3813a800cc8";

// tracking Manila
String city = "Manila";
String countryCode = "PH";

unsigned long lastTime = 0;
unsigned long timerDelay = 60000;  // Set timer to 1 minute

//rgbled set up, change the pin depending on the setup, using RGBled library
RGBLed led(14,12,13, RGBLed::COMMON_CATHODE);



void setup() {

// set the initial color 
led.setColor(244, 120, 88);


  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 1 minute, it will take 1 minute before the next reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status() == WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      String jsonBuffer = httpGETRequest(serverPath.c_str());

      JSONVar myObject = JSON.parse(jsonBuffer);
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

     // color scheme is mapped to weathericons of openweather APi 
      String mainDescription = myObject["weather"][0]["main"];
      Serial.print("Weather: ");
      Serial.println(mainDescription);
      
      String weatherIcon = myObject["weather"][0]["icon"];
      Serial.print("Weather Icon: ");
      Serial.println(weatherIcon);
      weatherIcon.toLowerCase();

      // This area is for controling the color of the LED based on the weather icons

      //day situations
      if (weatherIcon == "01d" || weatherIcon == "02d") {
        // Clear sky or few clouds during the day 
        led.setColor(RGBLed::CYAN);

      } else if (weatherIcon == "03d" || weatherIcon == "04d"  ) {
          // scattered and broken clouds during the day 
        led.setColor(RGBLed::BLUE);

      } else if (weatherIcon == "09d" || weatherIcon == "10d"  ) {
        // it's raining in manila d ka ba nilalamig?
        led.setColor(29, 162, 216);

      } else if (weatherIcon == "11d" ) {
        // thunderstorms bes
        led.setColor(16, 90, 146);


      //night situations

      }else if (weatherIcon == "01n" || weatherIcon == "02n") {
        // Clear sky or few clouds
        led.setColor(RGBLed::BLUE);

      } else if (weatherIcon == "03n" || weatherIcon == "04n"  ) {
         // scattered and broken clouds
        led.setColor(RGBLed::GREEN);

      } else if (weatherIcon == "09n" || weatherIcon == "10n"  ) {
         // it's raining in manila d ka ba nilalamig?
        led.setColor(29, 162, 216);

  
      } else if (weatherIcon == "11n" ) {
        // thunderstorms bes
        led.setColor(16, 90, 146);

      } else {
        // unknown conditions
       led.gradient(RGBLed::RED, RGBLed::GREEN, 200); 
      }

      
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return payload;
}
