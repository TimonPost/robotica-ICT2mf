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
    SharpTurnRight();
  }
  else if (detector.RightSideSensorsEnabled(sensorValues)) {
    SharpTurnLeft();
  } else if (detector.NoSensorsDetected(sensorValues)) {
    SharpTurnLeft();
  }else {
    car.Constant(Speed::Fastest);
  }

  for (int a = 0; a < 5; a++) {
    Serial.print(sensorValues[a]);
  }
  Serial.println();
  delay(25);
}

void SharpTurnLeft() {
  car.RightMotor().SetSpeed(Speed::Fastest);
  car.LeftMotor().Reverse(true);
}

void SharpTurnRight() {
    car.RightMotor().Reverse(true);
    car.LeftMotor().SetSpeed(Speed::Fastest);
}
