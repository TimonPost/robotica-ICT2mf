#include "Dispenser.h"

using namespace laad;

Dispenser::Dispenser(uint8_t pin) : servoPin(pin)
{
    servo.attach(servoPin);
    servo.write(0);
    //delay(500);
    servo.detach();
};

void Dispenser::dispense()
{
    servo.attach(servoPin);
    servo.write(90);
    delay(1000);
    servo.write(0);
    delay(300);
    servo.detach();
}