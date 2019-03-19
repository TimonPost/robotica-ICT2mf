#include "transporter.h"

Transporter::Transporter() 
{ 
    motor1 = Motor(EN1, IN1, LOWEST_POWER_VALUE_ENGINE1);
    motor2 =  Motor(EN2, IN2, LOWEST_POWER_VALUE_ENGINE2);
    motor1.Reverse(true); 
    motor2.Reverse(false);
}

/// Get the left motor of this transporter.
/// With the motor you set the speed and directions.
Motor& Transporter::LeftMotor() {
    return motor1;
}

/// Get the right motor of this transporter.
/// With the motor you set the speed and directions.
Motor& Transporter::RightMotor() {
    return motor2;
}

/// Make the transporter move in a constant way.
void Transporter::Constant(Speed speed) {
    motor1.SetSpeed(speed);
    motor2.SetSpeed(speed);
}

/// Stop the transporter. 
void Transporter::Stop() {
    motor1.SetSpeed(Speed::Stationair);
    motor2.SetSpeed(Speed::Stationair);
}