#include "s21_string.h"
#include "s21_utils.h"

char* specifierX(int number) {
  int numeralSystem = 16;
  return conversionDexInHexOrOcta(number, numeralSystem);
}