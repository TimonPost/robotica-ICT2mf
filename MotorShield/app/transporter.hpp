#ifndef _transporter_
#define _transporter_
 
#include "motor.hpp"
#include "speed.hpp"
#include "constants.hpp"
#define byte uint8_t

/// Abstracts away the transport car moving logic.
class Transporter {
    public:
    Motor leftMotor;
    Motor rightMotor;

    Transporter();
    
    /// Make the transporter move in a constant way.
    void constant(Speed speed);

    /// Stop the transporter. 
    void stop();
};
 #endif
