#include <Servo.h>

const int button = 2;
const int servoPin = 9;
const int ldrPin = A0;
const int threshold = 700; //threshold for the LDR
const int debounce = 200; //debounce time for the button
const int recheck = 100; //recheck time for the LDR
const bool v = true; //verbose

int pos = 0;
int ldrVal;
int i;
bool load = false; // bool for storing the status of the load

Servo servo; //servo to drop load


void setup() {
  pinMode(button, INPUT_PULLUP);
  servo.attach(servoPin);
  servo.write(pos);
  delay(800);
  servo.detach();
  if (v) {
    Serial.begin(9600);
  }
}

void loop() {
  if (digitalRead(button) == 0) {
    i++;
    if (v) {
      Serial.print("button pressed ");
      Serial.print(i);
      Serial.println(" times");
    }
    delay(debounce);
    load = !load;
    if (v) {
      Serial.print("Set load to ");
      Serial.println(load);
    }
  }

  if (load) {

    //Set display 1 to 'L'

    if (i == 1) {
      // set display 2 to '1'
    } else if (i == 2) {
      // set display 2 to '2'
    } else {
      // turn display off?? not sure yet
    }

    ldrVal = analogRead(ldrPin);  // read the input pin
    //Serial.println(ldrVal);
    if (ldrVal < threshold) {  //transporter gedetecteerd
      if (v) {
        Serial.println("Dark");
      }
      delay(recheck);
      ldrVal = analogRead(ldrPin);  // read the input pin
      if (ldrVal < threshold) {
        if (v) {
          Serial.println("Still dark, assuming transporter arrived. If not, check threshold");
        }
        servo.attach(servoPin);
        servo.write(90);  //push load out
        delay(400);
        servo.write(0);
        delay(400);
        servo.detach();
        load = !load;
        if (v) {
          Serial.print("Load (hopefully) dropped. \nSet load to ");
          Serial.println(load);
        }
      }
    }
  }

}

