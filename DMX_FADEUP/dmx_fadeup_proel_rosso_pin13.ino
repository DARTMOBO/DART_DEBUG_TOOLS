
#include "DmxSimple.h"

void setup() {
 
  DmxSimple.usePin(13);

  DmxSimple.maxChannel(4);
   DmxSimple.write(4, 255);
}

void loop() {
  int brightness;
  /* Simple loop to ramp up brightness */
  for (brightness = 0; brightness <= 255; brightness++) {
    
    /* Update DMX channel 1 to new brightness */
    DmxSimple.write(1, brightness);
    
    /* Small delay to slow down the ramping */
    delay(10);
  }

}
