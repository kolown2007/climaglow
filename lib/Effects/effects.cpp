#include "effects.h"

extern CRGB leds[]; // Declare the external LED array


//utility effects

void success() {
   digitalWrite(ledPin, HIGH);
   delay(500);
    digitalWrite(ledPin, LOW);
}


void wifiConnected(){
  fill_solid(leds, LED_COUNT, CRGB(255, 0, 0));
  FastLED.show();
}

// light effects

//KL lights

void KLsetSunriseColor() {
    fill_solid(leds, LED_COUNT, CRGB(220, 170, 140));  // Warm Soft Peach
    FastLED.show();
}

void KLsetEarlyMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(200, 160, 210)); // Pale Purple
    FastLED.show();
}

void KLsetMidMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(140, 190, 230)); // Sky Blue
    FastLED.show();
}

void KLsetLateMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(180, 200, 230)); // Light Blue
    FastLED.show();
}

void KLsetSolarNoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(100, 160, 220)); // Vibrant Blue
    FastLED.show();
}

void KLsetEarlyAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(220, 150, 140)); // Soft Coral
    FastLED.show();
}

void KLsetMidAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(200, 130, 180)); // Warm Pink
    FastLED.show();
}

void KLsetLateAfternoonColor() {

   CRGB startColor = CRGB(160, 100, 180); // Purple
   CRGB endColor = CRGB(120, 60, 140); // Soft Magenta

  fill_gradient_RGB(leds, 0, startColor, LED_COUNT - 1, endColor);

 FastLED.show();
}

void KLsetSunsetColor() {
    CRGB startColor = CRGB(120, 90, 140); // Deep Purple
    CRGB endColor = CRGB(80, 60, 100); // Nightfall Purple


   
    fill_gradient_RGB(leds, 0, startColor, LED_COUNT - 1, endColor);
    FastLED.show();
}





// Manila lights

void MLsetSunriseColor() {
   fill_gradient_HSV(leds, LED_COUNT,
        CHSV(4, 240, 255),     // Warm orange
        CHSV(42, 240, 255)     // Soft yellow
    );
    FastLED.show();
}

void MLsetEarlyMorningColor() {
  fill_gradient_HSV(leds, LED_COUNT,
        CHSV(280, 140, 255),   // Soft lavender (less saturation for pastel)
        CHSV(25, 160, 255)     // Warm peach
    );
    FastLED.show();
}

void MLsetMidMorningColor() {
    fill_gradient_HSV(leds, LED_COUNT,
        CHSV(50, 140, 255),    // Pale yellow (less saturation for soft look)
        CHSV(195, 170, 255)    // Sky blue
    );
    FastLED.show();
}

void MLsetLateMorningColor() {
  fill_gradient_HSV(leds, LED_COUNT,
        CHSV(160, 140, 255),   // Cool mint
        CHSV(180, 100, 255)    // Bright white-blue
    );
}

void MLsetSolarNoonColor() {
      static uint8_t brightness;
    EVERY_N_MILLISECONDS(50) {
        brightness = beatsin8(10, 180, 255); // Smooth pulsing every 6 seconds
    }
    
    fill_solid(leds, LED_COUNT, CHSV(185, 50, brightness)); // Cool blue-white with pulsing
    FastLED.show();
}

void MLsetEarlyAfternoonColor() {
      fill_gradient_HSV(leds, LED_COUNT,
        CHSV(195, 140, 255),   // Bright sky blue
        CHSV(210, 160, 255)    // Deep azure
    );
    FastLED.show();
}

void MLsetMidAfternoonColor() {
    fill_gradient_HSV(leds, LED_COUNT,
        CHSV(200, 160, 255),   // Warm afternoon blue
        CHSV(45, 180, 255)     // Soft golden
    );
    FastLED.show();
}

void MLsetLateAfternoonColor() {
    fill_gradient_HSV(leds, LED_COUNT,
        CHSV(35, 220, 255),    // Golden orange
        CHSV(25, 240, 255)     // Deep amber
    );
    FastLED.show();

}

void MLsetSunsetColor() {
    fill_gradient_HSV(leds, LED_COUNT,
        CHSV(10, 255, 255),    // Vibrant sunset orange
        CHSV(280, 240, 200)    // Deep purple sunset
    );
    FastLED.show();
}


void NightLights() {
    // Calculate 30% of total LEDs
    const int activeCount = LED_COUNT * 0.3;
    
    // Array to track which LEDs are active
    bool isActive[LED_COUNT] = {false};
    
    // Randomly select LEDs to activate
    for (int i = 0; i < activeCount; i++) {
        int ledIndex;
        do {
            ledIndex = random(LED_COUNT);
        } while (isActive[ledIndex]); // Ensure we don't select the same LED twice
        isActive[ledIndex] = true;
    }
    
    // Set LED colors
    for (int i = 0; i < LED_COUNT; i++) {
        if (isActive[i]) {
            uint8_t brightness = random(50, 255);
            CRGB color = CRGB(255, 248, 102); // Yellowish color
            leds[i] = color.nscale8(brightness);
        } else {
            leds[i] = CRGB::Black;
        }
    }
    
    FastLED.show();
    delay(100);
}



