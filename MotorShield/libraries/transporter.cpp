#include "transporter.h"

Transporter::Transporter() 
{ 
    this->motor1 = Motor(EN1, IN1, LOWEST_POWER_VALUE_ENGINE1);
    this->motor2 =  Motor(EN2, IN2, LOWEST_POWER_VALUE_ENGINE2);
    this->motor1.Reverse(true); 
}

//   void Transporter::LeftWeel () {

//   }

/// Set the speed of the left weel.
void Transporter::SetLeftWeelSpeed(Speed speed) {
    this->motor1.SetSpeed(speed);
}

/// Set the speed of the left weel.
void Transporter::SetRightWeelSpeed(Speed speed) {
this->motor2.SetSpeed(speed);
}

/// Make the transporter move in a constant way.
void Transporter::Car::Constant(Speed speed) {
    motor1.SetSpeed(speed);
    motor2.SetSpeed(speed);
}

/// Stop the transporter. 
void Transporter::Car::Stop() {
    motor1.SetSpeed(Speed::Stationair);
    motor2.SetSpeed(Speed::Stationair);
}