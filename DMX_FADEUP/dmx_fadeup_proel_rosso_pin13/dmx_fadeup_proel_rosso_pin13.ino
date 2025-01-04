
#include "DmxSimple.h"

void setup() {
 
  DmxSimple.usePin(13);

  DmxSimple.maxChannel(32);
   DmxSimple.write(4, 255);
    DmxSimple.write(5, 64);
}

void loop() {
  int brightness;
  /* Simple loop to ramp up brightness */
  for (brightness = 0; brightness <= 255; brightness++) {
    
    /* Update DMX channel 1 to new brightness */
    DmxSimple.write(5, brightness);
    
    /* Small delay to slow down the ramping */
    delay(10);
  }

}
