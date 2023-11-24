#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#include "s21_utils.h"

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

char* specifierE(double number) {
  char* charOfExponent = ((int)number == 0) ? "e-" : "e+";

  double fraction = fractionOfE(number);
  int exponentNum = exponent(number);
  char* result = doubleInChar(fraction);
  char* exponentStr = intInChar(exponentNum);
  printf("STR EXP**** %s\n", exponentStr);
  

  s21_strncat(result, charOfExponent, s21_strlen(charOfExponent));
  s21_strncat(result, exponentStr, s21_strlen(exponentStr));

  // if (s21_strncmp(exponentStr, "-e", s21_strlen(exponentStr))) exponentNum =
  // -exponentNum;  //проверка, убрать
  printf("CHAR EXP**** %10s\n", charOfExponent);
  printf("FRACTION NUMBER**** %f\n", fraction);
  // printf("EXPONENT**** %10d\n", exponentNum);
  printf("CHECK**** %10f\n", fraction * pow(10.0, exponentNum));

  return result;
}

int main() {
  char* line = malloc(sizeof(char) * 1000);
  double num = 3453453;

  sprintf(line, "*** SPRINTF E *** = %e", num);
  printf("%s\n", line);
  free(line);
  line = S21_NULL;
  printf("*******MY******** = %s\n", specifierE(num));
  return 0;
}