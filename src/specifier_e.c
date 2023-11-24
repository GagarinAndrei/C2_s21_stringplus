#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_files/s21_string.h"
#include "s21_utils.h"

char* exponentInStr(double number) { return ((int)number == 0) ? "e-" : "e+"; }

double fractionOfE(double number) {
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
  return result;
}

int exponent(double number) {
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
  int exponentNum = exponent(number);
  char* charOfExponent = exponentInStr(number);
  char* result =
      (char*)malloc(sizeof(char) * 2 * (s21_strlen(charOfExponent) + 1));
  if (result == S21_NULL) {
    printError(errno);
  }

  s21_strncat(result, charOfExponent, s21_strlen(charOfExponent));

  char* exponentStr = malloc(3 * sizeof(char));
  char* ptr = exponentStr;
  if (exponentNum < 10) {
    *ptr++ = '0';
    *ptr++ = (char)exponentNum + 48;
    *ptr = '\0';
  } else {
    exponentStr = intInChar(exponentNum);
  }
  s21_strncat(result, exponentStr, s21_strlen(exponentStr));
  char* resultPtr = result;
  free(result);
  return resultPtr;
}