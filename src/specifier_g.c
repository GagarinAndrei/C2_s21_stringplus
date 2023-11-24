#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "s21_utils.h"

char* specifierG(double number) { return 0; }

int main() {
  char* line = malloc(sizeof(char) * 1000);
  double num = 2342344;

  sprintf(line, "*** SPRINTF G *** = %g", num);
  printf("%s\n", line);
  printf("*******MY******** = %s", specifierG(num));

  return 0;
}