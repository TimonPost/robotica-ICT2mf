#include "arduino.h"
#include "SSD.h"
#include <stdint.h>

using namespace ssd;

uint8_t ssdPins[] = {4, 5, 6, 7, 8, 9, 10};
SSD seg7(3, 2, ssdPins);

void setup()
{
}

void loop()
{
  seg7.displayState(false, 4);
}
