#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"
#include "s21_utils.h"

double specifierG(double number) { return number; }

int main() {
  char* line = malloc(sizeof(char) * 1000);
  double num = 2342344;

  sprintf(line, "*** SPRINTF G *** = %g", num);
  printf("%s\n", line);
  printf("*******MY******** = %f", specifierG(num));

  return 0;
}