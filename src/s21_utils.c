#include "s21_utils.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h> //dfkpgssgmbkfdgmboksmbombordbdrmbhokrsmnoknsrkbmdhm

#include "lib_files/s21_string.h"

void printError(int error) {
  printf("%s\n", s21_strerror(error));
  exit(1);
}

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

// ПРЕОБРАЗОВАНИЕ DEC В OCTA
char* octaIntInChar(int number) {
  int numeralSystem = 8;
  return conversionDexInHexOrOcta(number, numeralSystem);
}

// ПРЕОБРАЗОВАНИЕ DEC В HEXA
char* hexaIntInChar(int number) {
  int numeralSystem = 16;
  return conversionDexInHexOrOcta(number, numeralSystem);
}

char* reverseStr(char *str){
    if (str == S21_NULL || *str == '\0') return S21_NULL;
    int end_str = s21_strlen(str);
    int i = 0;
    char* result = (char*)malloc(sizeof(char));
    while (i < s21_strlen(str)){
        result[i] =  str[end_str - 1];
        i++; 
        end_str--;
    }
    result[i] = '\0';
    free(result);
    return result;
}

// Преобразование адреса в строку
char *ptrInChar(int *address) {
  char *str = calloc(14, sizeof(char));
  char *ptr = str;
  
  s21_size_t *addressPtr = (s21_size_t*)address;
  if (addressPtr == NULL) {
    *str++ = '0';
  } else {
    while (addressPtr != 0 ) {
      s21_size_t lastSymbol = ((s21_size_t)addressPtr) % 16;
      lastSymbol < 10 ? (*str = 48 + lastSymbol)
                       : (*str = 87 + lastSymbol);
      addressPtr = ((s21_size_t *)(((s21_size_t)addressPtr) >> 4));
      *str++;
    }
  }
  *str = 'x';
  *str++;
  *str = '0';

  return reverseStr(ptr);
}

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


