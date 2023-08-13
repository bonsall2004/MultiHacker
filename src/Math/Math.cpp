#include "Math.h"

namespace Math {
  uint8_t FloorTen(uint8_t number) 
  {
    return (number / 15) * 15;
  }
  uint8_t RoundUp(uint8_t a, uint8_t b) 
  {
    if(a % b != 0) {
      return (a / b) + 1;
    } else {
      if((a / b) == 0) {
        return 1;
      } else {
        return (a / b);
      }
    }
  }
}
