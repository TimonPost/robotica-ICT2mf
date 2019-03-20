#include "detector.h"

LineDetector::LineDetector() {
    
}

boolean LineDetector::HasValue(int threshold, int pinType, int input){
  if (pinType == 4) {
    if (analogRead(input) > threshold){
      return 1;  
    } else {
      return 0;  
    }
  } else if (pinType == 3) {
    if(digitalRead(input)==HIGH) {
      return 1;  
    } else {
      return 0;  
    }
  } else {
    return false;
  }
}

bool LineDetector::MiddleSensorsEnabled(bool (&sensorValues)[5]) {
  return (sensorValues[2] == true);
}

bool LineDetector::LeftSideSensorsEnabled(bool (&sensorValues)[5]) {
  return (sensorValues[0] == true || sensorValues[1] == true);
}

bool LineDetector::RightSideSensorsEnabled(bool (&sensorValues)[5]) {
  return (sensorValues[3] == true || sensorValues[4] == true);
}

bool LineDetector::NoSensorsDetected(bool (&sensorValues)[5]) {
  return (sensorValues[0] == false || sensorValues[1] == false || sensorValues[2] == false || sensorValues[3] == false || sensorValues[4 == false]);
}

void LineDetector::GatherSensorResults(bool (&sensorValues)[5]) {
  sensorValues[0] = HasValue(800, 4, input0);
  sensorValues[1] = HasValue(800, 4, input1);
  sensorValues[2] = HasValue(0, 3, input4);
  sensorValues[3] = HasValue(800, 4, input2);
  sensorValues[4] = HasValue(800, 4, input3);
}
