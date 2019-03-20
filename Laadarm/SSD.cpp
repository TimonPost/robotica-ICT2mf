#include "arduino.h"
#include "SSD.h"

using namespace laad;

void _displayByte(uint8_t byte1, uint8_t byte2, SSD *pDisplay)
{
  SSD display = *pDisplay;

  uint8_t display1 = display.getDisplay(1);
  uint8_t display2 = display.getDisplay(2);

  uint8_t *pins = display.getSsdPorts();

  digitalWrite(display2, LOW);
  digitalWrite(display1, HIGH);
  for (unsigned char i = 0; i < 7; i++)
  {
    if (byte1 & 1 << i)
    {
      digitalWrite(pins[i], HIGH);
    }
    else
    {
      digitalWrite(pins[i], LOW);
    }
  }

  delay(10);

  digitalWrite(display1, LOW);
  digitalWrite(display2, HIGH);
  for (unsigned char i = 0; i < 7; i++)
  {
    if (byte2 & 1 << i)
    {
      digitalWrite(pins[i], HIGH);
    }
    else
    {
      digitalWrite(pins[i], LOW);
    }
  }

  delay(10);
}

SSD::SSD(uint8_t d1, uint8_t d2, uint8_t *p)
{
  display1 = d1;
  display2 = d2;

  ssdPorts = p;

  pinMode(display1, OUTPUT);
  digitalWrite(display1, HIGH);

  pinMode(display2, OUTPUT);
  digitalWrite(display2, HIGH);

  for (unsigned char i = 0; i < 7; i++)
  {
    pinMode(ssdPorts[i], OUTPUT);
    digitalWrite(ssdPorts[i], HIGH);
  }
}

uint8_t SSD::getDisplay(uint8_t display)
{
  if (display == 1)
  {
    return display1;
  }
  else
  {
    return display2;
  }

  return display1;
}

uint8_t *SSD::getSsdPorts()
{
  return ssdPorts;
}

void SSD::displayState(bool loaded, uint8_t number)
{
  unsigned char display2byte = 0b1001001;

  switch (number)
  {
  case 0:
    display2byte = 0b0111111;
    break;

  case 1:
    display2byte = 0b0110000;
    break;

  case 2:
    display2byte = 0b1011011;
    break;

  case 3:
    display2byte = 0b1001111;
    break;

  case 4:
    display2byte = 0b1100110;
    break;

  case 5:
    display2byte = 0b1101101;
    break;

  case 6:
    display2byte = 0b1111101;
    break;

  case 7:
    display2byte = 0b0000111;
    break;

  case 8:
    display2byte = 0b1111111;
    break;

  case 9:
    display2byte = 0b1101111;
    break;
  }

  _displayByte((loaded ? 0b0111000 : 0b1111001), display2byte, this);
}
