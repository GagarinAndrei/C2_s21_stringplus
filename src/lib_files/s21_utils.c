#include "s21_utils.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// #include <string.h> //dfkpgssgmbkfdgmboksmbombordbdrmbhokrsmnoknsrkbmdhm

#include "s21_string.h"
void printError(int error) {
  printf("%s\n", s21_strerror(error));
  exit(1);
}

// считает количество % в строке формата
int formatCounter(const char *string) {
  int result = 0;
  for (s21_size_t i = 0; i < s21_strlen(string); i++) {
    if (*(string + i) == '%') {
      result++;
    }
  }

  return result;
}

// Преобразует int в строку и возвращает указатель на нее
char *intInChar(long long int number) {
  int isNegative = 0;
  if (number < 0) {
    isNegative = 1;
    number *= -1;
  }
  int i = digitsInIntCounter(number);
  char *result = (char *)calloc(i, sizeof(char));
  if (result == S21_NULL) {
    printError(errno);
  }

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

  return result;
}

// Возвращает количество цифр в целом числе
int digitsInIntCounter(long long int n) {
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
char *doubleInChar(long double number) {
  double beforeComma, afterComma;
  afterComma = modf(number, &beforeComma);
  if (afterComma < 0) {
    afterComma *= -1;
  }
  char *result = malloc(sizeof(char));

  char *beforeCommaString = intInChar(beforeComma);
  char *beforePtr = beforeCommaString;
  int i = 0;

  while (*beforeCommaString) {
    result[i++] = *beforeCommaString++;
    result = realloc(result, sizeof(char));
  }
  result[i++] = '.';
  result = realloc(result, sizeof(char));

  afterComma += 0.0000000005;
  afterComma *= 1000000000;

  while ((int)afterComma % 10 == 0 && afterComma != 0) {
    afterComma /= 10;
  }

  char *afterCommaString = intInChar((int)afterComma);
  char *afterPtr = afterCommaString;

  while (*afterCommaString) {
    result[i++] = *afterCommaString++;
    result = realloc(result, sizeof(char));
  }

  free(afterPtr);
  free(beforePtr);

  return result;
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
char *conversionDexInHexOrOcta(int number, int numeralSystem) {
  int i = 0;
  int prevNumber = number;
  int maxIntDiv = prevNumber;
  int tmpNumber = 0;
  char *result = (char *)malloc(sizeof(int) * i);
  if (result == S21_NULL) {
    printError(errno);
  }
  int *tmpResult = (int *)malloc(sizeof(int));
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
  // free(result);
  return result;
}

// ПРЕОБРАЗОВАНИЕ DEC В OCTA
char *octaIntInChar(int number) {
  int numeralSystem = 8;
  return conversionDexInHexOrOcta(number, numeralSystem);
}

// ПРЕОБРАЗОВАНИЕ DEC В HEXA
char *hexaIntInChar(int number) {
  int numeralSystem = 16;
  return conversionDexInHexOrOcta(number, numeralSystem);
}

char *reverseStr(char *str) {
  if (str == S21_NULL || *str == '\0')
    return S21_NULL;
  int end_str = s21_strlen(str);
  s21_size_t i = 0;
  char *result = (char *)malloc(sizeof(char));
  while (i < s21_strlen(str)) {
    result[i] = str[end_str - 1];
    i++;
    end_str--;
  }
  result[i] = '\0';
  // free(result);
  return result;
}

// Преобразование адреса в строку
char *ptrInChar(int *address) {
  char *str = calloc(14, sizeof(char));
  char *ptr = str;

  s21_size_t *addressPtr = (s21_size_t *)address;
  if (addressPtr == NULL) {
    *str++ = '0';
  } else {
    while (addressPtr != 0) {
      s21_size_t lastSymbol = ((s21_size_t)addressPtr) % 16;
      lastSymbol < 10 ? (*str = 48 + lastSymbol) : (*str = 87 + lastSymbol);
      addressPtr = ((s21_size_t *)(((s21_size_t)addressPtr) >> 4));
      *str = *(str + 1);
    }
  }
  *str = 'x';
  *str = *(str + 1);
  *str = '0';

  return reverseStr(ptr);
}

char *exponentInStr(double number) {
  return ((int)number == 0 && number != 0) ? "e-" : "e+";
}

double fractionOfE(double number) {
  if (number == 0)
    return 0;
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
  if (number == 0)
    return 0;
  if (number < 0)
    number = -number;

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

char *exponentOfE(double number) {
  char *resultPtr = "";
  int exponentNum = exponent(number);
  char *charOfExponent = exponentInStr(number);
  char *result = (char *)malloc(sizeof(char));
  resultPtr = result;
  if (result == S21_NULL) {
    printError(errno);
  }

  while (*charOfExponent != '\0')
    *result++ = *charOfExponent++;

  char *exponentStr = malloc(3 * sizeof(char));
  char *ptr = exponentStr;
  if (exponentNum < 10) {
    *ptr++ = '0';
    *ptr++ = (char)exponentNum + 48;
    *ptr = '\0';
  } else {
    exponentStr = intInChar(exponentNum);
  }

  while (*exponentStr)
    *result++ = *exponentStr++;
  *result = '\0';

  // free(resultPtr);
  return resultPtr;
}

long double roundTo(long double number, short precision) {
  double div = 1.0;
  if (precision < 0) {
    while (precision++) {
      div /= 10.0;
    }
  } else {
    while (precision--) {
      div *= 10.0;
    }
  }
  return floorl(number * div + 0.5) / div;
}