#include "motor.h"

Motor::Motor() {
}

Motor::Motor(byte enginePin, byte directionPin, byte lowest_power_value) 
{ 
    this->enginePin = enginePin;
    this->directionPin = directionPin;
    this->lowest_power_value = lowest_power_value;
}   

/// This will calulate the power needed for the provided `Speed`. 
byte Motor::GetSpeed(Speed speed, byte lowest_power_value) {
    switch (speed)
    {
        case Speed::Stationair:
            return MIN_POWER_VALUE;
        case Speed::Fastest:
            return MAX_POWER_VALUE;
        default:
            byte factor = (MAX_POWER_VALUE - lowest_power_value) / 5;
            return lowest_power_value + (factor * (byte)speed);  
    }    
}

/// Set the motor speed by the given speed.
void Motor::SetSpeed(Speed speed) {
    byte pwd = this->GetSpeed(speed, this->lowest_power_value);
    analogWrite(this->enginePin, pwd);
}

/// Set the motor speed by the given value.
/// Where 0 is no speed and 255 is maximal speed. 
/// 
/// # Remark 
/// The motor has resistant from gears and envoirment, 
/// becuse of this the given `val` could not get this motor in movement.
void Motor::SetSpeedByVal(byte val) {
    analogWrite(this->enginePin, val);
}

/// Make to motor turn into the opposite direction.
void Motor::Reverse(bool reverse) {
    if (reverse) {
        digitalWrite(this->directionPin, HIGH);
    }else {
        digitalWrite(this->directionPin, LOW);
    }
}
