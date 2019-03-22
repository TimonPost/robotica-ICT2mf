#include "transporter.hpp"
#include "speed.hpp"
#include "lineDetector.hpp"
#include "constants.hpp"
#include "direction.hpp"

#define byte uint8_t

Transporter car;
LineDetector detector;
Direction lastDetection;

void setup()
{
  car = Transporter();
  detector = LineDetector();
  car.Stop();

  for (int i = 4; i <= 7; i++){
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
    bool sensorValues[NUMBER_OF_LINE_SENSORS];

  // Getting sensorValues
  detector.gatherSensorResults(sensorValues);
  
  if (detector.leftSideSensorsEnabled(sensorValues)) { 
    turnRight();
    lastDetection = Direction::left;
  } else if (detector.rightSideSensorsEnabled(sensorValues)) {
    turnLeft();
    lastDetection = Direction::right;
  } else if(detector.middleSensorsEnabled(sensorValues)) {
    
    // if turning and we are on the line, we should disable one weel from spinning reverse.
    // if (lastDetection == Direction::left) 
    //   car.leftMotor.reverse(false);
    // else if (lastDetection == Direction::right)
    //   car.leftMotor.reverse(false);

    car.constant(Speed::Fastest);
  } else if (detector.noSensorsDetected(sensorValues)) {
    if (lastDetection == Direction::left) {
      turnRight();
    } else if (lastDetection == Direction::right) {
      turnLeft();
    } else {
      
    }  
  } else {
    car.stop();
  }

        // if turning and we are on the line, we should disable one weel from spinning reverse.
        // if (lastDetection == "left")
        //     car.LeftMotor().Reverse(false);
        // else if (lastDetection == "right")
        //     car.LeftMotor().Reverse(false);

        car.Constant(Speed::Slow);
    }
    else if (detector.NoSensorsDetected(sensorValues))
    {
        if (lastDetection == "left")
        {
            TurnRight();
        }
        else if (lastDetection == "right")
        {
            TurnLeft();
        }
    }
    else
    {
        car.Stop();
    }

    // Debug for sensorValues
    for (int a = 0; a < 5; a++)
    {
        Serial.print(sensorValues[a]);
    }
    Serial.println();
}

void turnLeft() {
  car.rightMotor.setSpeed(Speed::Fastest);
}

void turnRight() {
  car.rightMotor.reverse(true);
}
