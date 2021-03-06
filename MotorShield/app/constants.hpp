#ifndef _constants_
#define _constants_
#include <stdint.h>
#include "Arduino.h"
#include "speed.hpp"
#define byte uint8_t

const byte EN1 = 6;
const byte IN1 = 7;
const byte IN2 = 4;
const byte EN2 = 5;

const byte LOWEST_POWER_VALUE_ENGINE1 = 180;
const byte LOWEST_POWER_VALUE_ENGINE2 = 180;

const byte MIN_POWER_VALUE = 0;
const byte MAX_POWER_VALUE = 255;

const int NUMBER_OF_LINE_SENSORS = 5;

const Speed TURN_MINIMUM_SPEED = Speed::Stationair;
const Speed TURN_MAXIMUM_SPEED = Speed::Fast;
const Speed DEFAULT_CONSTANT_SPEED = Speed::Fast;

// 4 pin sensors
const int INPUT0 = A0;
const int INPUT1 = A1;
const int INPUT2 = A2;
const int INPUT3 = A3;

// 3 pin sensor
const int INPUT4 = 3;

const int buttonPin = 4;

#endif
