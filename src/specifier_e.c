#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib_files/s21_string.h"
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

char* exponentInStr(double number) { return ((int)number == 0) ? "e-" : "e+"; }

char* specifierE(double number) {
  int exponentNum = exponent(number);
  double fraction = fractionOfE(number);
  char* charOfExponent = exponentInStr(number);
  char* fractionStr = doubleInChar(fraction);
  // char result[1000] = {0};
  char* result =
      (char*)malloc(sizeof(char) * 2 * (s21_strlen(fractionStr) + 1));
  if (result == S21_NULL) {
    printError(errno);
  }

  // printf("STRLEN**** %d\n", s21_strlen(fractionStr));
  // result = (char*)realloc(result, sizeof(char) * s21_strlen(fractionStr)*2);
  s21_strncat(result, fractionStr, s21_strlen(fractionStr));
  s21_strncat(result, charOfExponent, s21_strlen(charOfExponent));

  // char* exponentStr = intInChar(exponentNum);
  // if (exponentNum < 10) exponentStr = s21_insert(exponentStr, "0", 0);
  char* exponentStr = malloc(3 * sizeof(char));
  char* ptr = exponentStr;
  if (exponentNum < 10) {
    *ptr++ = '0';
    *ptr++ = (char)exponentNum + 48;
    *ptr = '\0';
  } else {
    exponentStr = intInChar(exponentNum);
  }
  printf("STR EXP**** %s\n", exponentStr);
  s21_strncat(result, exponentStr, s21_strlen(exponentStr));

  // if (s21_strncmp(exponentStr, "-e", s21_strlen(exponentStr))) exponentNum =
  // -exponentNum;  //проверка, убрать
  printf("CHAR EXP**** %10s\n", charOfExponent);
  printf("FRACTION NUMBER**** %f\n", fraction);
  printf("EXPONENT* %d *** %10s\n", exponentNum, exponentStr);
  printf("CHECK**** %10f\n", fraction * pow(10.0, exponentNum));
  char* resultPtr = result;
  return resultPtr;
}

int main() {
  char* line = malloc(sizeof(char) * 1000);
  double num;

  sprintf(line, "*** SPRINTF E *** = %e", num);
  printf("%s\n", line);
  free(line);
  line = S21_NULL;
  printf("*******MY******** = %s\n", specifierE(num));
  return 0;
}