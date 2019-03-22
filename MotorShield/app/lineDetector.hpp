#ifndef _sensor_
#define _sensor_

#include "constants.hpp"
#include "Arduino.h"
#define byte uint8_t

class LineDetector {   
    private: 
        bool hasValue(int threshold, int pinType, int input);
    public:
        void gatherSensorResults(bool (&sensorValues)[5]);
        bool middleSensorsEnabled(bool (&sensorValues)[5]);
        bool leftSideSensorsEnabled(bool (&sensorValues)[5]);
        bool rightSideSensorsEnabled(bool (&sensorValues)[5]);
        bool noSensorsDetected(bool (&sensorValues)[5]);        
};
 #endif
