#include "leap.h"

bool leap_year(int year) {
  if (year % 100 == 0) {
    return year % 400 == 0;
  }
  return year % 4 == 0;
}
