#include "arduino.h"
#include "SSD.h"
#include "Button.h"
#include "LightSensor.h"
#include <stdint.h>

using namespace laad;

uint8_t n = 0;

uint8_t ssdPins[] = {4, 5, 6, 7, 8, 9, 10};
SSD seg7(3, 2, ssdPins);
Button button(11);
LS ls(5, 50);

void stage()
{
  n++;
  bool stillLoaded = true;
  while (true)
  {
    if (ls.isDark())
    {
      stillLoaded = false;
    }

    if (!stillLoaded)
      button.onPress(stage);

    seg7.displayState(stillLoaded, n);
  }
}

void setup()
{
}

void loop()
{
  //seg7.displayState(false, 0);
  button.onPress(stage);
}
