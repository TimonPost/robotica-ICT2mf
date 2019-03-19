#include "transporter.h"
#include "speed.h"

#define byte uint8_t
Transporter car;

void setup()
{
  car = Transporter();
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
  
  String reading = String(IsLine(200, 4, input0)) + String(IsLine(200, 4, input1)) + String(IsLine(0, 3, input4)) + String(IsLine(200, 4, input2)) + String(IsLine(200, 4, input3));
  Serial.println(reading);
  if (reading == "00100") {
    // Straight ahead  
  } else if (reading == "11100") {
    // hard right
  } else if (reading == "00111") {
    // hard left
  } else if (reading == "01100") {
    // smooth right
  } else if (reading == "00110") {
    // smooth left
  } else if(reading == "00000") {
    // no line found
  } else {
    // default
  }
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
