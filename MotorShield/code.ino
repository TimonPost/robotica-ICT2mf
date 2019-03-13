byte EN1 = 6;
byte IN1 = 7;

byte IN2 = 4; //Latest version use pin 4 instead of pin 8
byte EN2 = 5;  //Roboduino Motor shield uses Pin 9

const byte LOWEST_POWER_VALUE_ENGINE1 = 190;
const byte LOWEST_POWER_VALUE_ENGINE2 = 190;

const byte MIN_POWER_VALUE = 0;
const byte MAX_POWER_VALUE = 255;

const byte NUMBER_OF_SPEED_VALUES = 4;

enum Speed {
  Stationair,
  VerySlow,
  Fastest,

  Slow = 1, 
  Average = 2,
  Fast = 3,
  VeryFast = 4,
};

// void Motor1(byte pwm, boolean reverse) {
//   analogWrite(EN1, pwm); //set pwm control, 0 for stop, and 255 for maximum speed
//   if (reverse)  {
//     digitalWrite(IN1, HIGH);
//   }
//   else  {
//     digitalWrite(IN1, LOW);
//   }
// }

class Motor {   
  private: 
    byte enginePin;
    byte directionPin;
    byte lowest_power_value;

    byte Motor::GetSpeed(Speed speed, byte lowest_power_value) {

      switch (speed)
      {
        case Speed::Stationair:
          return MIN_POWER_VALUE;
        case Speed::Fastest:
          return MAX_POWER_VALUE;
        case Speed::VerySlow:
          return MIN_POWER_VALUE;
        default:
          byte factor = (MAX_POWER_VALUE - lowest_power_value) / 4;
          Serial.println(factor);
          return lowest_power_value + (factor * (byte)speed);  
      }    
    }

    public:
      Motor() 
      {
         enginePin = 0;
         directionPin = 0;
         lowest_power_value = 0;
      }

      Motor(byte enginePin, byte directionPin, byte lowest_power_value) 
      { 
        enginePin = enginePin;
        directionPin = directionPin;
        lowest_power_value = lowest_power_value;

         digitalWrite(directionPin, HIGH);
      }   

      void Motor::SetSpeed(Speed speed) {
          byte pwd = this->GetSpeed(speed, this->lowest_power_value);
          // Serial.println(pwd);
          analogWrite(this->enginePin, pwd);
      }

      void Motor::Reverse(bool reverse) {
        // todo
      }
};

class Car {
    private:
        Motor motor1;
        Motor motor2;

    public:
        Car() 
        { 
            motor1 = Motor(EN1, IN1, LOWEST_POWER_VALUE_ENGINE1);
            motor2 = Motor(EN2, IN2, LOWEST_POWER_VALUE_ENGINE2);
        }

        void TurnLeft() {

        }

        void TurnRight() {

        }

        void Car::Constant() {
            motor1.SetSpeed(Speed::Fastest);
            // motor2.SetSpeed(Speed::Fastest);
        }

        void Car::Stop() {
            motor1.SetSpeed(Speed::Stationair);
            // motor2.SetSpeed(Speed::Stationair);
        }
};

void setup() {
  for (int i = 4; i <= 7; i++)
    pinMode(i, OUTPUT); 

  Serial.begin(9600);
}

void loop() {
  Car car = Car();
  car.Constant();
  delay(3000);
  car.Stop();
  delay(3000);
}