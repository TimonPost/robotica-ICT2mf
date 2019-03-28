#include "transporter.hpp"
#include "speed.hpp"
#include "lineDetector.hpp"
#include "constants.hpp"
#include "direction.hpp"
#include "Button.h"
#include "transporterLoaderModule.hpp"
#define byte uint8_t

const int SENSOR_COUNT = 5;
const int BUFFER_SIZE = 10;

Transporter car;
Direction lastDetection;
LineDetector lineDetector;
laad::Button btn(buttonPin);
bool sensorValues[SENSOR_COUNT];
TransporterLoaderModule *transporterLoaderModule;

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
  pinMode(9, OUTPUT);
  transporterLoaderModule = new TransporterLoaderModule(13,9);

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

bool sensorCycleBuffer[BUFFER_SIZE][SENSOR_COUNT];
int bufferIndex = 0;
bool mergedSensors[SENSOR_COUNT];

void updateMergedSensors() {
	memset(mergedSensors, 0, sizeof(mergedSensors));
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		for (int j = 0; j < SENSOR_COUNT; j++) {
			mergedSensors[j] = mergedSensors[j] | sensorCycleBuffer[i][j];
		}
	}
}

void gatherSensorResultsWrapper()
{
		lineDetector.gatherSensorResults(sensorValues);
		for (int i = 0; i < SENSOR_COUNT; i++) {
			sensorCycleBuffer[bufferIndex][i] = sensorValues[i];
		}
		updateMergedSensors();
		bufferIndex = ++bufferIndex % BUFFER_SIZE;
}

void followLineUntilTSplit()
{
  Serial.println("followLineUntilTSplit");
  goStraight();
  while(true){
    delay(25);
    gatherSensorResultsWrapper();
    if(!lineDetector.tSplitDetected(sensorValues))
    {
      delay(100);
      Serial.println("out of tsplit");
      break;
    }
  }
  
  while (true)
  {
    delay(25);

    // Getting sensorValues
    gatherSensorResultsWrapper();

    Serial.print(sensorValues[0]);
    Serial.print(sensorValues[1]);
    Serial.print(sensorValues[2]);
    Serial.print(sensorValues[3]);
    Serial.print(sensorValues[4]);
    Serial.println();


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
    else if(lineDetector.tSplitDetected(mergedSensors))
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
  Serial.println("dropCargo");
  car.stop();
  transporterLoaderModule->unloadCargo();
  delay(2000);
}

void loadCargo()
{
  car.stop();
  while(true){
    delay(50);
    if(transporterLoaderModule->hasCargo()){
      break;
    }
  }
}

void turnRightA(){
  turnRight();
  lastDetection = Direction::right;
  delay(400);
}

void turnLeftA(){
  turnLeft();
  lastDetection = Direction::left;
  delay(400);
}

void stop(){
  car.stop();
}

typedef void (*voidFuncPtr)();

void loopAfterPressed()
{
  voidFuncPtr ignoreTSplit = followLineUntilTSplit;

  const int ROUTESECTIONCOUNT = 21;
  voidFuncPtr route[ROUTESECTIONCOUNT] = {
      //Start
      followLineUntilTSplit,
      ignoreTSplit,
      ignoreTSplit,
      loadCargo,
      followLineUntilTSplit,
      turnRightA,
      followLineUntilTSplit,
      dropCargo,

      followLineUntilTSplit,
      ignoreTSplit,
      loadCargo,
      followLineUntilTSplit,

      turnRightA,
      followLineUntilTSplit,
      ignoreTSplit,
      dropCargo,
      ignoreTSplit,
      followLineUntilTSplit,

      turnLeftA,
      followLineUntilTSplit,
      stop
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
    //car.stop();
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