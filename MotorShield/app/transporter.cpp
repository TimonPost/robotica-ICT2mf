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

void Transporter::turnLeft(bool mostLeftSensorEnabled, bool leftSensorEnabled)
{
  if (mostLeftSensorEnabled)
  {
    rightMotor.setSpeed(Speed::Fastest);
  }
  if (leftSensorEnabled)
  {
    rightMotor.setSpeed(Speed::Average);
  }
  
  leftMotor.setSpeed(TURN_MINIMUM_SPEED);
}

void Transporter::turnRight(bool mostRightSensorEnabled, bool rightSensorEnabled)
{
  if (rightSensorEnabled)
  {
    leftMotor.setSpeed(Speed::Average);
  }
  if (mostRightSensorEnabled)
  {
    leftMotor.setSpeed(Speed::Fastest);
  }

  rightMotor.setSpeed(TURN_MINIMUM_SPEED);
}
