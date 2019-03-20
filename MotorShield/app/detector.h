#ifndef _sensor_
 #define _sensor_

#include "constants.h"
#include "Arduino.h"
#define byte uint8_t

class LineDetector {   
    private: 
        bool HasValue(int threshold, int pinType, int input);
    public:
        LineDetector();
        void GatherSensorResults(bool (&sensorValues)[5]);
        bool MiddleSensorsEnabled(bool (&sensorValues)[5]);
        bool LeftSideSensorsEnabled(bool (&sensorValues)[5]);
        bool RightSideSensorsEnabled(bool (&sensorValues)[5]);
        bool LineDetector::NoSensorsDetected(bool (&sensorValues)[5]);        
};
 #endif
