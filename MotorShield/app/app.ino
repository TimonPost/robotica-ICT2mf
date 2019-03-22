#include "transporter.h"
#include "speed.h"
#include "detector.h"
#include "constants.h"

#define byte uint8_t

Transporter car;
LineDetector detector;
char *lastDetection = "";
bool ignition = false;
int buttonState = 0;
int lastButtonState = 0;

void setup()
{
    car = Transporter();
    car.Stop();

    for (int i = 4; i <= 7; i++)
    {
        pinMode(i, OUTPUT);
    }
    pinMode(input0, INPUT);
    pinMode(input1, INPUT);
    pinMode(input2, INPUT);
    pinMode(input3, INPUT);
    pinMode(buttonPin, INPUT);

    // pinMode(input4, INPUT);

    Serial.begin(9600);
}

void loop()
{
    buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH)
    {
        delay(25);
        detector = LineDetector();

        bool sensorValues[NUMBER_OF_LINE_SENSORS];

        // Getting sensorValues
        detector.GatherSensorResults(sensorValues);

        if (detector.LeftSideSensorsEnabled(sensorValues))
        {
            TurnRight();
            lastDetection = "left";
        }
        else if (detector.RightSideSensorsEnabled(sensorValues))
        {
            TurnLeft();
            lastDetection = "right";
        }
        else if (detector.MiddleSensorsEnabled(sensorValues))
        {

            // if turning and we are on the line, we should disable one weel from spinning reverse.
            if (lastDetection == "left")
                car.LeftMotor().Reverse(false);
            else if (lastDetection == "right")
                car.LeftMotor().Reverse(false);

            car.Constant(Speed::Slow);
        }
        else if (detector.NoSensorsDetected(sensorValues))
        {
            if (lastDetection == "left")
            {
                TurnRight();
            }
            else if (lastDetection == "right")
            {
                TurnLeft();
            }
            else
            {
            }
        }
        else
        {
            car.Stop();
        }

        // Debug for sensorValues
        for (int a = 0; a < 5; a++)
        {
            Serial.print(sensorValues[a]);
        }

        Serial.println();

        // The smaller the delay, the more the robot will read the sensors
    }
    else
    {
        car.Stop();
    }
}

void IgnitionStateUpdate()
{
    byte isPressed = digitalRead(buttonPin);

    if (isPressed)
    {
        if (ignition == true)
        {
            ignition = false;
        }
        else
        {
            ignition = true;
        }
    }
}

void TurnLeft()
{
    car.RightMotor().SetSpeed(Speed::Slow);
    car.LeftMotor().Reverse(true);
}

void TurnRight()
{
    car.RightMotor().Reverse(true);
    car.LeftMotor().SetSpeed(Speed::Slow);
}
