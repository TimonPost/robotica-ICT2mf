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

bool LineDetector::LeftSideSensorsEnabled(bool (&sensorValues)[5]) {
    return (sensorValues[0] == true || sensorValues[1] == true);
}

bool LineDetector::RightSideSensorsEnabled(bool (&sensorValues)[5]) {
    return (sensorValues[3] == true || sensorValues[4] == true);
}

void LineDetector::GatherSensorResults(bool (&sensorValues)[5]) {
    sensorValues[0] = HasValue(200, 4, input0);
    sensorValues[1] = HasValue(200, 4, input1);
    sensorValues[2] = HasValue(200, 3, input4);
    sensorValues[3] = HasValue(200, 4, input2);
    sensorValues[4] = HasValue(200, 4, input3);

   return sensorValues;
}