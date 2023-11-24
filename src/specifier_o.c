#include "s21_string.h"
#include "s21_utils.h"

// ПРЕОБРАЗОВАНИЕ DEC В HEXA
char* specifierO(int number) {
  int numeralSystem = 8;
  return conversionDexInHexOrOcta(number, numeralSystem);
}