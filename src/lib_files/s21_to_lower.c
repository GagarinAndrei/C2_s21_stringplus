#include <stdlib.h>

#include "s21_string.h"

char make_char_lower(char c) {
  char result = c;
  if (c >= 'A' && c <= 'Z') result = c - ('A' - 'a');

  return result;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  size_t len = s21_strlen(str);
  char *line = (char *)malloc(len + 1);
  if (line == S21_NULL) {
    return S21_NULL;
  }

  for (size_t i = 0; i < len; i++) {
    line[i] = make_char_lower(str[i]);
  }
  line[len] = '\0';
  free(line);
  return line;
}