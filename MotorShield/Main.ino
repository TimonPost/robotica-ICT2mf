#include "libraries/transporter.h"
#include "libraries/speed.cpp"

void setup() {
  for (int i = 4; i <= 7; i++)
    pinMode(i, OUTPUT); 

  Serial.begin(9600);
}

void loop() {
  Transporter car = Transporter();
  car.Stop();
  delay(2000);
  car.Constant(Speed::VerySlow);
  delay(2000);
  car.Constant(Speed::Slow);
  delay(2000);
  car.Constant(Speed::Average);
  delay(2000);
  car.Constant(Speed::Fast);
  delay(2000);
  car.Constant(Speed::VeryFast);
  delay(2000);
  car.Constant(Speed::Fastest);
  delay(2000);
}