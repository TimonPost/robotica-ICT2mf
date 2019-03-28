#include "lineDetector.hpp"

boolean LineDetector::hasValue(int threshold, int pinType, int input)
{
  if (pinType == 4)
  {
    if (analogRead(input) > threshold)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else if (pinType == 3)
  {
    if (digitalRead(input) == HIGH)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}

bool LineDetector::middleSensorsEnabled(bool (&sensorValues)[5])
{
  return (sensorValues[0] == false && sensorValues[1] == false && sensorValues[2] == true && sensorValues[3] == false && sensorValues[4] == false);
}

bool LineDetector::leftSideSensorsEnabled(bool (&sensorValues)[5])
{
  return ((sensorValues[0] == true || sensorValues[1] == true) && sensorValues[2] == false && sensorValues[3] == false && sensorValues[4] == false);
}

bool LineDetector::rightSideSensorsEnabled(bool (&sensorValues)[5])
{
  return (sensorValues[0] == false && sensorValues[1] == false && sensorValues[2] == false && (sensorValues[3] == true || sensorValues[4] == true));
}

bool LineDetector::noSensorsDetected(bool (&sensorValues)[5])
{
  return (sensorValues[0] == false && sensorValues[1] == false && sensorValues[2] == false && sensorValues[3] == false && sensorValues[4] == false);
}

bool LineDetector::specialMarkDetected(bool (&sensorValues)[5])
{
  return (sensorValues[0] == true && sensorValues[1] == false && sensorValues[2] == true && sensorValues[3] == false && sensorValues[4] == true);
}

bool LineDetector::tSplitDetected(bool (&sensorValues)[5])
{
  return (sensorValues[0] == true && sensorValues[1] == true && sensorValues[3] == true && sensorValues[4] == true);
}

void LineDetector::gatherSensorResults(bool (&sensorValues)[5])
{
  sensorValues[0] = hasValue(800, 4, INPUT0);
  sensorValues[1] = hasValue(800, 4, INPUT1);
  sensorValues[2] = hasValue(0, 3, INPUT4);
  sensorValues[3] = hasValue(800, 4, INPUT2);
  sensorValues[4] = hasValue(800, 4, INPUT3);
}
