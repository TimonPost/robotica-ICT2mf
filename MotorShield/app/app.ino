#include "transporter.h"
#include "speed.h"
#include "detector.h"

#define byte uint8_t

Transporter car;

void setup()
{
  car = Transporter();
  for (int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(input0, INPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);

  Serial.begin(9600);
}

void loop()
{ 
  LineDetector detector = LineDetector();

  const int size=5;
  bool sensorValues[size];

  detector.GatherSensorResults(sensorValues);

  if (detector.LeftSideSensorsEnabled(sensorValues)) {
    SharpTurnLeft();
  }
  else if (detector.RightSideSensorsEnabled(sensorValues)) {
    SharpTurnRight();
  } else {
    car.Constant(Speed::Slow);
  }

  for (int a = 0; a < 5; a++) {
    Serial.print(sensorValues[a]);
  }
  Serial.println();
}

void SharpTurnLeft() {
  car.RightMotor().SetSpeed(Speed::VeryFast);
  car.LeftMotor().SetSpeed(Speed::Stationair);
}

void SharpTurnRight() {
    car.RightMotor().SetSpeed(Speed::Stationair);
    car.LeftMotor().SetSpeed(Speed::VeryFast);
}