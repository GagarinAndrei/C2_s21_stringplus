#include "s21_string.h"

size_t s21_strlen(const char *str) {
  size_t length = 0;
  while (*str != '\0') {
    length++;
    str++;
  }
  return length;
}