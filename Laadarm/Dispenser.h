#include "arduino.h"
#include <Servo.h>
#include <stdlib.h>

namespace laad
{
class Dispenser
{
  private:
    uint8_t servoPin;
    Servo servo;

  public:
    Dispenser(uint8_t pin);
    void dispense();
};

} // namespace laad