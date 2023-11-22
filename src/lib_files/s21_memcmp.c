#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  while ((*((char *)str1) != '\0' || *((char *)str2) != '\0') && n != 0) {
    if (*((char *)str1) != *((char *)str2)) {
      return *((char *)str1) - *((char *)str2);
    }
    n--;
    str1++;
    str2++;
  }

  return 0;
}
