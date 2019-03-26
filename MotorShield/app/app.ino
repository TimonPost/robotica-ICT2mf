#include "transporter.hpp"
#include "speed.hpp"
#include "lineDetector.hpp"
#include "constants.hpp"
#include "direction.hpp"
#include "Button.h"

#define byte uint8_t

Transporter car;
Direction lastDetection;
LineDetector lineDetector;
laad::Button btn(buttonPin);
bool sensorValues[NUMBER_OF_LINE_SENSORS];

void setup()
{
  car = Transporter();
  lineDetector = LineDetector();
  car.stop();

  for (int i = 4; i <= 7; i++)
  {
    pinMode(i, OUTPUT);
  }

  pinMode(INPUT0, INPUT);
  pinMode(INPUT1, INPUT);
  pinMode(INPUT2, INPUT);
  pinMode(INPUT3, INPUT);

  for (int i = 4; i <= 7; i++)
  {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600);
}

void loop()
{
  btn.onPress(loopAfterPressed);
}

void loopAfterPressed()
{
  while (true)
  {
    // Getting sensorValues
    lineDetector.gatherSensorResults(sensorValues);

    if (lineDetector.middleSensorsEnabled(sensorValues))
    {
      goStraight();
      lastDetection = Direction::straight;
    }
    else if (lineDetector.leftSideSensorsEnabled(sensorValues))
    {
      turnLeft();
      lastDetection = Direction::left;
    }
    else if (lineDetector.rightSideSensorsEnabled(sensorValues))
    {
      turnRight();
      lastDetection = Direction::right;
    }
    else if (lineDetector.noSensorsDetected(sensorValues))
    {
      if (lastDetection == Direction::left)
      {
        turnLeft();
      }
      if (lastDetection == Direction::right)
      {
        turnRight();
      }
    }
    else if (lineDetector.specialMarkDetected(sensorValues))
    {
      car.stop();
    }
    else
    {
      figureDirection();
    }

    Serial.print(sensorValues[0]);
    Serial.print(sensorValues[1]);
    Serial.print(sensorValues[2]);
    Serial.print(sensorValues[3]);
    Serial.print(sensorValues[4]);
    Serial.println();
  }
}

void figureDirection()
{
  Serial.println(lastDetection);
  if (lastDetection == Direction::left)
  {
    turnLeft();
  }
  if (lastDetection == Direction::right)
  {
    turnRight();
  }
  if (lastDetection == Direction::straight)
  {
    goStraight();
  }
  else
  {
    car.stop();
  }
}

const Speed TURN_MINIMUM_SPEED = Speed::Stationair;
const Speed TURN_MAXIMUM_SPEED = Speed::Fast;
const Speed DEFAULT_CONSTANT_SPEED = Speed::Fast;

void goStraight()
{
  car.rightMotor.reverse(false);
  car.rightMotor.reverse(false);
  car.constant(DEFAULT_CONSTANT_SPEED);
}

void turnLeft()
{
  if (sensorValues[0])
  {
    car.rightMotor.setSpeed(Speed::Fastest);
  }
  if (sensorValues[1])
  {
    car.rightMotor.setSpeed(Speed::Average);
  }
  
  car.leftMotor.setSpeed(TURN_MINIMUM_SPEED);
}

void turnRight()
{
  if (sensorValues[3])
  {
    car.leftMotor.setSpeed(Speed::Average);
  }
  if (sensorValues[4])
  {
    car.leftMotor.setSpeed(Speed::Fastest);
  }

  car.rightMotor.setSpeed(TURN_MINIMUM_SPEED);
}