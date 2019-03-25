#include "Button.h"

using namespace laad;

Button::Button(uint8_t pin)
{
  inputPin = pin;
  pinMode(pin, INPUT);
}

bool Button::isPressed()
{
  if (digitalRead(inputPin))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Button::onPress(void (*f)())
{
  if (isPressed())
  {
    while (isPressed());
    (*f)();
  }
}