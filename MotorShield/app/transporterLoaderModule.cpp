#include "transporterLoaderModule.hpp"
#include <Servo.h>

TransporterLoaderModule::TransporterLoaderModule(int laserPin, int servoPin)
{
    this->laserPin = laserPin;
    this->servo = Servo();
    this->servo.attach(servoPin);
    this->servo.write(90);
}

bool TransporterLoaderModule::hasCargo(){
    return digitalRead(this->laserPin) == 0;
}

void TransporterLoaderModule::unloadCargo(){
    for(int i = 90;i > 0;i-=5)
    {
        this->servo.write(i);
        delay(50);
    }
    this->servo.write(90);
}


