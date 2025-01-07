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
    fill_solid(leds, LED_COUNT, CRGB(255, 248, 220)); // Soft Creamy White
    FastLED.show();
}

void KLsetEarlyMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(245, 235, 200)); // Pale Yellow
    FastLED.show();
}

void KLsetMidMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(224, 255, 255)); // Cool Blue-White
    FastLED.show();
}

void KLsetLateMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(200, 230, 255)); // Subtle Sky Blue
    FastLED.show();
}

void KLsetSolarNoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(180, 230, 255)); // Vibrant Sky Blue
    FastLED.show();
}

void KLsetEarlyAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 225, 204)); // Soft Peach
    FastLED.show();
}

void KLsetMidAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 200, 170)); // Warm Coral
    FastLED.show();
}

void KLsetLateAfternoonColor() {

   CRGB startColor = CRGB(255, 183, 153); // Soft Peach
   CRGB endColor = CRGB(255, 102, 178); // Gentle Pink

  fill_gradient_RGB(leds, 0, startColor, LED_COUNT - 1, endColor);

 FastLED.show();
}

void KLsetSunsetColor() {
 CRGB startColor = CRGB(255, 102, 178); // Gentle Pink
 CRGB endColor = CRGB(153, 102, 204); // Muted Lavender

   
    fill_gradient_RGB(leds, 0, startColor, LED_COUNT - 1, endColor);
    FastLED.show();
}


// void KLsetSunsetColor() {
//     // Define the start and end colors for the gradient
//     CRGB startColor = CRGB(255, 102, 178); // Gentle Pink
//     CRGB endColor = CRGB(153, 102, 204); // Muted Lavender

//     // Fill the LED array with a gradient from startColor to endColor
//     fill_gradient_RGB(leds, 0, startColor, LED_COUNT - 1, endColor);
//     FastLED.show();

//     // Smooth fades with occasional subtle pulses
//     for (int i = 0; i < 256; i++) {
//         FastLED.setBrightness(i);
//         FastLED.show();
//         delay(10);
//     }

//     for (int i = 255; i >= 0; i--) {
//         FastLED.setBrightness(i);
//         FastLED.show();
//         delay(10);
//     }

//     // Subtle pulse effect
//     for (int j = 0; j < 3; j++) {
//         for (int i = 0; i < 256; i += 5) {
//             FastLED.setBrightness(i);
//             FastLED.show();
//             delay(5);
//         }

//         for (int i = 255; i >= 0; i -= 5) {
//             FastLED.setBrightness(i);
//             FastLED.show();
//             delay(5);
//         }
//     }
// }







// Manila lights

void MLsetSunriseColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 223, 186)); // Warm Yellow
    FastLED.show();
}

void MLsetEarlyMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 245, 210)); // Soft Warm Cream
    FastLED.show();
}

void MLsetMidMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 255, 204)); // Light Yellow
    FastLED.show();
}

void MLsetLateMorningColor() {
    fill_solid(leds, LED_COUNT, CRGB(240, 255, 240)); // Mint Green
    FastLED.show();
}

void MLsetSolarNoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(224, 255, 255)); // Cool Blue-White
    FastLED.show();
}

void MLsetEarlyAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(200, 240, 255)); // Sky Blue
    FastLED.show();
}

void MLsetMidAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 230, 200)); // Warm Peach
    FastLED.show();
}

void MLsetLateAfternoonColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 200, 150)); // Golden Orange
    FastLED.show();
}

void MLsetSunsetColor() {
    fill_solid(leds, LED_COUNT, CRGB(255, 102, 0)); // Bright Orange transitioning to Deep Red
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



