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

void loopAfterPressed()
{
  while (true)
  {
    bool sensorValues[NUMBER_OF_LINE_SENSORS];

    // Getting sensorValues
    lineDetector.gatherSensorResults(sensorValues);

    if (lineDetector.leftSideSensorsEnabled(sensorValues))
    {
      turnRight();
      lastDetection = Direction::left;
    }
    else if (lineDetector.rightSideSensorsEnabled(sensorValues))
    {
      turnLeft();
      lastDetection = Direction::right;
    }
    else if (lineDetector.middleSensorsEnabled(sensorValues))
    {

      // if turning and we are on the line, we should disable one weel from spinning reverse.
      // if (lastDetection == Direction::left)
      //   car.leftMotor.reverse(false);
      // else if (lastDetection == Direction::right)
      //   car.leftMotor.reverse(false);

      car.constant(Speed::Average);
    }
    else if (lineDetector.noSensorsDetected(sensorValues))
    {
      if (lastDetection == Direction::left)
      {
        turnRight();
      }
      else if (lastDetection == Direction::right)
      {
        turnLeft();
      }
      else
      {
      }
    }
    else
    {
      car.stop();
    }
    Serial.println(sensorValues[2]);
  }
}

void loop()
{
  btn.onPress(loopAfterPressed);
}

void turnLeft()
{
  car.rightMotor.setSpeed(Speed::Average);
  car.leftMotor.setSpeed(Speed::Stationair);
}

void turnRight()
{
  car.rightMotor.setSpeed(Speed::Stationair);
  car.leftMotor.setSpeed(Speed::Average);
}