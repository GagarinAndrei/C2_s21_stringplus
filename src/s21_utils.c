#include "s21_utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "lib_files/s21_string.h"

// считает количество % в строке формата
int formatCounter(const char* string) {
  int result = 0;
  for (s21_size_t i = 0; i < s21_strlen(string); i++) {
    if (*(string + i) == '%') {
      result++;
    }
  }

  return result;
}

// Преобразует int в строку и возвращает указатель на нее
char* intInChar(int number) {
  int isNegative = 0;
  if (number < 0) {
    isNegative = 1;
    number *= -1;
  }
  int i = digitsInIntCounter(number);
  char* result = (char*)calloc(i, sizeof(char));
  if (result == S21_NULL) {
    printError(errno);
  }

  char* ptr = result;
  int n = 0;

  if (isNegative) {
    i++;
  }
  while (i > 0) {
    n = number % 10;
    result[--i] = n + 48;
    number = number / 10;
  }
  if (isNegative) {
    result[0] = '-';
  }
  result[s21_strlen(result)] = '\0';
  free(result);
  return ptr;
}

// Возвращает количество цифр в целом числе
int digitsInIntCounter(int n) {
  int i = 0;
  if (n / 10 == 0) {
    return 1;
  } else {
    while (n > 0) {
      n = n / 10;
      i++;
    }
    return i;
  }
};

// Преобразует double в строку и возвращает указатель на нее
char* doubleInChar(double number) {
  double beforeComma, afterComma;
  afterComma = modf(number, &beforeComma);
  char* result = malloc(sizeof(char));
  char* ptr = result;
  char* beforeCommaString = intInChar(beforeComma);
  int i = 0;

  while (*beforeCommaString) {
    result[i++] = *beforeCommaString++;
    result = realloc(result, sizeof(char));
  }
  result[i++] = '.';
  result = realloc(result, sizeof(char));

  afterComma += 0.0000000005;
  afterComma *= 1000000000;

  while ((int)afterComma % 10 == 0) {
    afterComma /= 10;
  }

  char* afterCommaString = intInChar((int)afterComma);

  while (*afterCommaString) {
    result[i++] = *afterCommaString++;
    result = realloc(result, sizeof(char));
  }

  free(result);
  return ptr;
}

// Преобразование строки в число
int strInInt(char ch) {
  int result = -1;

  if (ch >= '0' && ch <= '9') {
    result = ch - 48;
  }
  return result;
}

// Преобразование десятичного числа в восьмеричное или шестнадцатиричное
char* conversionDexInHexOrOcta(int number, int numeralSystem) {
  int i = 0;
  int prevNumber = number;
  int maxIntDiv = prevNumber;
  int tmpNumber = 0;
  char* result = (char*)malloc(sizeof(int) * i);
  if (result == S21_NULL) {
    printError(errno);
  }
  int* tmpResult = (int*)malloc(sizeof(int));
  if (tmpResult == S21_NULL) {
    printError(errno);
  }
  if (number != 0) {
    while (maxIntDiv > 0) {
      tmpResult = realloc(tmpResult, sizeof(int) * i + 1);
      if (tmpResult == S21_NULL) {
        printError(errno);
      }
      tmpNumber = maxIntDiv % numeralSystem;
      maxIntDiv = maxIntDiv / numeralSystem;
      prevNumber = maxIntDiv;
      tmpResult[i] = tmpNumber;
      i++;
    }
    i--;
  }

  int j = 0;
  while (i >= 0) {
    if (tmpResult[i] > 9) {
      result[j] = (char)(tmpResult[i] + 87);
    } else {
      result[j] = intInChar(tmpResult[i])[0];
    }
    j++;
    i--;
  }

  result[j] = '\0';

  free(tmpResult);
  free(result);
  return result;
}

void printError(int error) {
  printf("%s\n", s21_strerror(error));
  exit(1);
}