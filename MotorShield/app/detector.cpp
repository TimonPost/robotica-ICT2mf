#include "sensor.h"

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

bool LineDetector::LeftSideSensorsEnabled(bool sensors[5]) {
    return (sensors[0] == true || sensors[1] == true);
}

bool LineDetector::RightSideSensorsEnabled(bool sensors[5]) {
    return (sensors[3] == true || sensors[4] == true);
}

bool* LineDetector::GatherSensorResults () {
   bool enabledSensors[5] = { false, false, false, false, false };

    enabledSensors[0] = HasValue(200, 4, input0);
    enabledSensors[1] = HasValue(200, 4, input1);
    enabledSensors[2] = HasValue(200, 3, input4);
    enabledSensors[3] = HasValue(200, 4, input2);
    enabledSensors[4] = HasValue(200, 4, input3);

   return enabledSensors;
}