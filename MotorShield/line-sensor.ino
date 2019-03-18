// 4 pin sensors
const int input0 = A0; 
const int input1 = A1;
const int input2 = A2;
const int input3 = A3;

// 3 pin sensor
const int input4 = 3;

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

void setup()  {
  Serial.begin(9600);
  pinMode(input0, INPUT);
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  pinMode(input3, INPUT);
}

void loop()  {
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
