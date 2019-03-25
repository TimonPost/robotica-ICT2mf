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

void loop()
{
  btn.onPress(loopAfterPressed);
}

void loopAfterPressed()
{
  while (true)
  {
    bool sensorValues[NUMBER_OF_LINE_SENSORS];

    // Getting sensorValues
    lineDetector.gatherSensorResults(sensorValues);

    if (lineDetector.middleSensorsEnabled(sensorValues))
    {
      car.constant(Speed::Fastest);
    }
    else if (lineDetector.leftSideSensorsEnabled(sensorValues))
    {
      turnRight();
      lastDetection = Direction::left;
    }
    else if (lineDetector.rightSideSensorsEnabled(sensorValues))
    {
      turnLeft();
      lastDetection = Direction::right;
    }
    else if (lineDetector.noSensorsDetected(sensorValues))
    {
      if (lastDetection == Direction::left)
      {
        turnRight();
        lastDetection = Direction::left;
      }
      if (lastDetection == Direction::right)
      {
        turnLeft();
         lastDetection = Direction::right;
      }
    }
    else if(lineDetector.specialMarkDetected(sensorValues)) {
      car.stop();
    }
    else {
      turnRight();
    }

    Serial.print(sensorValues[0]);
    Serial.print(sensorValues[1]);
    Serial.print(sensorValues[2]);
    Serial.print(sensorValues[3]);
    Serial.print(sensorValues[4]);
    Serial.println();
  }
}

void turnLeft()
{
  car.leftMotor.setSpeed(Speed::Average);
  car.rightMotor.setSpeed(Speed::Stationair);
}

void turnRight()
{
  car.leftMotor.setSpeed(Speed::Stationair);
  car.rightMotor.setSpeed(Speed::Average);
}