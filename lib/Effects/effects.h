#ifndef EFFECTS_H
#define EFFECTS_H

#include <FastLED.h>
#include "config.h"


// Utility effects
void success();
void wifiConnected();

// KL lights
void KLsetSunriseColor();
void KLsetEarlyMorningColor();
void KLsetMidMorningColor();
void KLsetLateMorningColor();
void KLsetSolarNoonColor();
void KLsetEarlyAfternoonColor();
void KLsetMidAfternoonColor();
void KLsetLateAfternoonColor();
void KLsetSunsetColor();

// Manila lights
void MLsetSunriseColor();
void MLsetEarlyMorningColor();
void MLsetMidMorningColor();
void MLsetLateMorningColor();
void MLsetSolarNoonColor();
void MLsetEarlyAfternoonColor();
void MLsetMidAfternoonColor();
void MLsetLateAfternoonColor();
void MLsetSunsetColor();


#endif