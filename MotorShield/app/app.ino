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

void followLineUntilTSplit()
{
  bool sensorValues[NUMBER_OF_LINE_SENSORS];

  goStraight();
  while(true){
    lineDetector.gatherSensorResults(sensorValues);
    if(!lineDetector.tSplitDetected(sensorValues))
    {
      break;
    }
  }
  
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
      car.turnLeft(sensorValues[0], sensorValues[1]);
      lastDetection = Direction::left;
    }
    else if (lineDetector.rightSideSensorsEnabled(sensorValues))
    {
      car.turnRight(sensorValues[4], sensorValues[3]);
      lastDetection = Direction::right;
    }
    else if (lineDetector.noSensorsDetected(sensorValues))
    {
      if (lastDetection == Direction::left)
      {
        car.turnLeft(sensorValues[0], sensorValues[1]);
      }
      if (lastDetection == Direction::right)
      {
        car.turnRight(sensorValues[4], sensorValues[3]);
      }
    }
    else if(lineDetector.tSplitDetected(sensorValues))
    {
      return;
    }
    else
    {
      figureDirection();
    }
  }
}

void dropCargo()
{
  car.stop();
  delay(1000);
}

void loadCargo()
{
  car.stop();
  delay(2000);
}

void turnRightA(){
  car.turnRight(sensorValues[4], sensorValues[3]);
  delay(500);
}

typedef void (*voidFuncPtr)();

void loopAfterPressed()
{
  voidFuncPtr ignoreTSplit = followLineUntilTSplit;


  const int ROUTESECTIONCOUNT = 8;
  voidFuncPtr route[ROUTESECTIONCOUNT] = {
      followLineUntilTSplit,
      ignoreTSplit,
      ignoreTSplit,
      loadCargo,
      followLineUntilTSplit,
      turnRightA,
      followLineUntilTSplit,
      dropCargo,
      };

  for (int i = 0; i < ROUTESECTIONCOUNT; i++)
  {
    route[i]();
  }
}

void figureDirection()
{
  Serial.println(lastDetection);
  if (lastDetection == Direction::left)
  {
    car.turnLeft(sensorValues[0], sensorValues[1]);
  }
  if (lastDetection == Direction::right)
  {
    car.turnRight(sensorValues[4], sensorValues[3]);
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

void goStraight()
{
  car.rightMotor.reverse(false);
  car.rightMotor.reverse(false);
  car.constant(DEFAULT_CONSTANT_SPEED);
}