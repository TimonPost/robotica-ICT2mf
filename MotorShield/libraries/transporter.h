#include "motor.h"
#include "speed.cpp"
#include "constants.cpp"

/// Abstracts away the transport car moving logic.
class Transporter {
    private:
        Motor motor1;
        Motor motor2;

    public:
    Transporter();
    
    //   void LeftWeel ();

    /// Set the speed of the left weel.
    void SetLeftWeelSpeed(Speed speed);

    /// Set the speed of the left weel.
    void SetRightWeelSpeed(Speed speed);

    /// Make the transporter move in a constant way.
    void Transporter::Constant(Speed speed);

    /// Stop the transporter. 
    void Transporter::Stop();
};