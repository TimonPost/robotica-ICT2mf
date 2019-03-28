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
  car.turnRight();
  lastDetection = Direction::right;
  delay(400);
}

void turnLeftA(){
  car.turnLeft();
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
    //car.stop();
  }
}

void goStraight()
{
  car.rightMotor.reverse(false);
  car.rightMotor.reverse(false);
  car.constant(DEFAULT_CONSTANT_SPEED);
}