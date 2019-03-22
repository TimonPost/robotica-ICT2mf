#include "transporter.hpp"

Transporter::Transporter()
{
    leftMotor = Motor(EN1, IN1, LOWEST_POWER_VALUE_ENGINE1);
    rightMotor = Motor(EN2, IN2, LOWEST_POWER_VALUE_ENGINE2);
    leftMotor.reverse(false); 
    rightMotor.reverse(false);
}

/// Make the transporter move in a constant way.
void Transporter::constant(Speed speed)
{
    leftMotor.setSpeed(speed);
    rightMotor.setSpeed(speed);
}

/// Stop the transporter.
void Transporter::stop()
{
    leftMotor.setSpeed(Speed::Stationair);
    rightMotor.setSpeed(Speed::Stationair);
}
