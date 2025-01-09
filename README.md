# CLIMAGLOW_KL

## project by Rhaz Oriente

### Specs
- the development uses platform.io on vscode not on arduino IDE.
- https://platformio.org/

### Tools
- ESP32 - https://en.wikipedia.org/wiki/ESP32
- Neopixel LEDs - https://www.adafruit.com/category/168

### Readings
 - https://esp32io.com/tutorials/esp32-neopixel-led-strip

 ### LED controls
- FastLED - https://fastled.io/

#### sunset API
- https://sunrise-sunset.org/api

### Metro Manila Coordinates
- 14.5995° N, 120.9842° E
-  https://api.sunrise-sunset.org/json?lat=14.5995&lng=120.9842&tzid=Asia/Manila

### Kuala Lumpur Coordinates
- 3.1499° N, 101.6945° E
- https://api.sunrise-sunset.org/json?lat=3.1499&lng=101.6945&tzid=Asia/Kuala_Lumpur

### File Structure
- the main loop is in main.cpp
- config setup is in setup.h and setup.cpp
- led effects is in effects.h and effects.cpp

### builtin LEDS indicators
- red means function call success
- blue led means fail.
- if blue just press the EN button on esp32 to refresh

### no of LEDs.
 - this is the total no of LEDs in the strip connection.
 - edit config.h line no. 6, the default is 8 coz testing setup has 8 leds

### How to Connect to WIFI
 - first time connection: connect to Climaglow hotspot, pw: kolown1234
 - open browser on phone/laptop and go to 192.168.4.1
 - connect to the available wifi, it will save the credentials

 ### Manila vs KL controllers
 - for KL edit line 21 on config.cpp -->  http.begin(sunsetAPI_KL);
 - for KL edit void loop on main.cpp --> comment the MLsetup

 - for ML edit line 21 on config.cpp -->  http.begin(sunsetAPI_ML);
 -  for ML edit void loop on main.cpp --> comment the KLsetup

### The LED effects are saved on effects.cpp file
 - note: this file is under development for color testing

### Grabe ang artist na to, teh matoto ka mag jira siguro next time


