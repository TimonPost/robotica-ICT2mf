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

void loop() { 
  LineDetector detector = LineDetector();

  const int size=5;
  bool sensorValues[size];

  // Getting sensorValues
  detector.GatherSensorResults(sensorValues);
  
  if (detector.LeftSideSensorsEnabled(sensorValues)) { 
    TurnRight();
  } else if (detector.RightSideSensorsEnabled(sensorValues)) {
    TurnLeft();
  } else if (detector.NoSensorsDetected(sensorValues)) {
    TurnLeft();
  } else {
    car.Constant(Speed::Fastest);
  }

  // Debug for sensorValues
  for (int a = 0; a < 5; a++) {
    Serial.print(sensorValues[a]);
  }
  Serial.println();

  // The smaller the delay, the more the robot will read the sensors
  delay(25);
}

void TurnLeft() {
  car.RightMotor().SetSpeed(Speed::Fastest);
  car.LeftMotor().Reverse(true);
}

void TurnRight() {
  car.RightMotor().Reverse(true);
  car.LeftMotor().SetSpeed(Speed::Fastest);
}
