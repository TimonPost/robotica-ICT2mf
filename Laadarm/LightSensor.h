#include "arduino.h"
#include <stdint.h>

namespace laad
{
class LS
{
private:
  uint32_t threshold;
  uint8_t inputPin;

public:
  LS(uint8_t, uint32_t);

  bool isDark();
};
} // namespace laad
