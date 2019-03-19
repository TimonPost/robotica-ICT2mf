#include "transporter.h"
#include "speed.h"

#define byte uint8_t

void setup()
{
  for (int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(input0, INPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);

  Serial.begin(9600);
}

void loop()
{
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

  // Calibrations for the pins.
  // IsLine(150, 4, input0);
  // IsLine(100, 4, input1);
  // IsLine(0, 3, input4);
  // IsLine(100, 4, input2);
  // IsLine(100, 4, input3);
  
  String reading = String(IsLine(200, 4, input0)) + String(IsLine(200, 4, input1)) + String(IsLine(0, 3, input4)) + String(IsLine(200, 4, input2)) + String(IsLine(200, 4, input3));
  Serial.println(reading);

  delay(100);

}

boolean IsLine(int threshold, int pinType, int input){
  if (pinType == 4) {
    //Serial.println(analogRead(input));
    if (analogRead(input) > threshold){
      return 1;  
    } else {
      return 0;  
    }
  } else if (pinType == 3) {
    if(digitalRead(input)==HIGH) {
      return 1;  
    } else {
      return 0;  
    }
  } else {
    return false;
  }
}
