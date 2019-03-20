#include "LightSensor.h"

using namespace laad;

LS::LS(uint8_t inputPin, uint32_t threshold)
{
  (*this).inputPin = inputPin;
  (*this).threshold = threshold;
}

bool LS::isDark()
{
  return (analogRead(inputPin) < threshold);
}