// Преобразует int в строку и возвращает указатель на нее
// Возвращает количество цифр в целом числе
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

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

char *intInChar(int number) {
  int isNegative = 0;
  if (number < 0) {
    isNegative = 1;
    number *= -1;
  }
  int i = digitsInIntCounter(number);
  char *result = (char *)calloc(i, sizeof(char));
  if (result == S21_NULL) {
    printf("Memory not allocated.\n");
    exit(0);
  }

  char *ptr = result;
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

  free(result);
  return ptr;
}
