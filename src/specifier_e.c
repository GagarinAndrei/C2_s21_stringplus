#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_files/s21_string.h"
#include "s21_utils.h"

char* exponentInStr(double number) {
  return ((int)number == 0 && number != 0) ? "e-" : "e+";
}

double fractionOfE(double number) {
  if (number == 0) return 0;
  int minus = 0;
  if (number < 0) {
    number = -number;
    minus = 1;
  }
  double result = number;

  if ((int)result == 0) {
    while ((int)result < 1) {
      result *= 10;
    }
  } else {
    while ((int)result / 10 != 0) {
      result /= 10;
    }
  }

  return (minus) ? -result : result;
}

int exponent(double number) {
  if (number == 0) return 0;
  if (number < 0) number = -number;

  int result = 0;
  if ((int)number == 0) {
    while ((int)number < 1) {
      number *= 10;
      result++;
    }
  } else {
    while ((int)number / 10 != 0) {
      number /= 10;
      result++;
    }
  }
  return result;
}

char* exponentOfE(double number) {
  char* resultPtr = "";
  int exponentNum = exponent(number);
  char* charOfExponent = exponentInStr(number);
  char* result = (char*)malloc(sizeof(char));
  resultPtr = result;
  if (result == S21_NULL) {
    printError(errno);
  }

  while (*charOfExponent != '\0') *result++ = *charOfExponent++;

  char* exponentStr = malloc(3 * sizeof(char));
  char* ptr = exponentStr;
  if (exponentNum < 10) {
    *ptr++ = '0';
    *ptr++ = (char)exponentNum + 48;
    *ptr = '\0';
  } else {
    exponentStr = intInChar(exponentNum);
  }
  free(exponentStr);

  while (*exponentStr) *result++ = *exponentStr++;
  *result = '\0';

  free(resultPtr);
  return resultPtr;
}

int main() {
  char* line = malloc(sizeof(char) * 1000);
  double num = 4.0;
  sprintf(line, "***SPRINTF*** = %e\n", num);
  printf(line);
  printf("S21_SPRINTF*** = %f", fractionOfE(num));
  printf("%s\n", exponentOfE(num));

  free(line);

  return 0;
}