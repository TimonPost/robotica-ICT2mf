#include "arduino.h"
#include "SSD.h"
#include "Button.h"
#include "LightSensor.h"
#include "Dispenser.h"
#include <stdint.h>
#include <Servo.h>

using namespace laad;

uint8_t tripN = 0;
//                   A, B, C, D, E, F, G
uint8_t ssdPins[] = {6, 7, 10, 9, 8, 5, 4};
SSD seg7(2, 3, ssdPins);
Button button(13);
LS ls(5, 80);
Dispenser d(11);

void trip()
{
  tripN++;
  bool stillLoaded = true;
  while (true)
  {
    if (ls.isDark() && stillLoaded)
    {
      d.dispense();
      stillLoaded = false;
    }

    if (!stillLoaded)
      button.onPress(trip);

    seg7.displayState(stillLoaded, tripN);
  }
}

void setup()
{
}

void loop()
{
  //seg7.displayState(false, 8);
  button.onPress(trip);
}
