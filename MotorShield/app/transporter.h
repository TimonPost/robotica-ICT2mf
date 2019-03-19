#ifndef _transporter_
 #define _transporter_
 
#include "motor.h"
#include "speed.h"
#include "constants.h"
#define byte uint8_t

/// Abstracts away the transport car moving logic.
class Transporter {
    private:
        Motor motor1;
        Motor motor2;

    public:
    Transporter();
    
    /// Get the left motor of the transporter.
    Motor& LeftMotor();

    /// Get the right motor of the transporter.
    Motor& RightMotor();

    /// Make the transporter move in a constant way.
    void Transporter::Constant(Speed speed);

    /// Stop the transporter. 
    void Transporter::Stop();
};
 #endif
