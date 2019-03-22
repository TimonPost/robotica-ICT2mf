#ifndef _motor_
#define _motor_

#include "speed.hpp"
#include "constants.hpp"
#include "Arduino.h"
#define byte uint8_t

class Motor
{
private:
  byte enginePin;
  byte directionPin;
  byte lowest_power_value;

    /// This will calulate the power needed for the provided `Speed`. 
    byte getSpeed(Speed speed, byte lowest_power_value);

public:
  Motor();

  Motor(byte enginePin, byte directionPin, byte lowest_power_value);

      /// Set the motor speed by the given speed.
      void setSpeed(Speed speed);

      /// Set the motor speed by the given value.
      /// Where 0 is no speed and 255 is maximal speed. 
      /// 
      /// # Remark 
      /// The motor has resistant from gears and envoirment, 
      /// becuse of this the given `val` could not get this motor in movement.
      void setSpeedByVal(byte val);

      /// Make to motor turn into the opposite direction.
      void reverse(bool reverse);
};
#endif
