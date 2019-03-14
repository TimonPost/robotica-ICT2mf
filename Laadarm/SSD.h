#include "arduino.h"
#include <stdint.h>

namespace ssd
{
class SSD
{
private:
  uint8_t display1;
  uint8_t display2;

  uint8_t *ssdPorts;

public:
  SSD(uint8_t, uint8_t, uint8_t *);

  void displayState(bool, uint8_t);
  uint8_t getDisplay(uint8_t);
  uint8_t *getSsdPorts();
};
} // namespace ssd