#ifndef TRANSPORTERLOADERMODULE_HPP
#define TRANSPORTERLOADERMODULE_HPP

#include "arduino.h"
#include <Servo.h>

class TransporterLoaderModule
{
public:
  TransporterLoaderModule(int laserPin, int servo);
  bool hasCargo();
  void unloadCargo();

private:
  int laserPin;
  Servo servo;
};

#endif