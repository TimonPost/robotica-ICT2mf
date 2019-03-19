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
        bool* GatherSensorResults();
        bool LeftSideSensorsEnabled(bool sensors[5]);
        bool RightSideSensorsEnabled(bool sensors[5]);
};
 #endif
