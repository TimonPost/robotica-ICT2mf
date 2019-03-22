#include "lineDetector.hpp"

<<<<<<< HEAD
LineDetector::LineDetector()
{
}
=======
>>>>>>> format

boolean LineDetector::hasValue(int threshold, int pinType, int input){
  if (pinType == 4) {
    if (analogRead(input) > threshold){
      return 1;  
    } else {
      return 0;  
    }
    else
    {
      return 0;
    }
  }
  else if (pinType == 3)
  {
    if (digitalRead(input) == HIGH)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return false;
  }
}

bool LineDetector::middleSensorsEnabled(bool (&sensorValues)[5]) {
  return (sensorValues[2] == true);
}

bool LineDetector::leftSideSensorsEnabled(bool (&sensorValues)[5]) {
  return (sensorValues[0] == true || sensorValues[1] == true);
}

bool LineDetector::rightSideSensorsEnabled(bool (&sensorValues)[5]) {
  return (sensorValues[3] == true || sensorValues[4] == true);
}

bool LineDetector::noSensorsDetected(bool (&sensorValues)[5]) {
  return (sensorValues[0] == false || sensorValues[1] == false || sensorValues[2] == false || sensorValues[3] == false || sensorValues[4 == false]);
}

void LineDetector::gatherSensorResults(bool (&sensorValues)[5]) {
  sensorValues[0] = hasValue(800, 4, INPUT0);
  sensorValues[1] = hasValue(800, 4, INPUT1);
  sensorValues[2] = hasValue(0, 3,   INPUT4);
  sensorValues[3] = hasValue(800, 4, INPUT2);
  sensorValues[4] = hasValue(800, 4, INPUT3);
}
