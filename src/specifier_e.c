#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"
#include "s21_utils.h"

char* specifierE(double number) {
    char* result;
    result = malloc(sizeof(char));
    int leftSide = 0;
    int isPositiv = 0;
    int exponent = 0;
    char charOfExponent = ((int)number == 0)? '-' : '+'; 
    if (number > 1) leftSide = 1;
    if (number > 0)  isPositiv = 1;
    


       
    
    return 0; }

int main() {
  char* line = malloc(sizeof(char) * 1000);
  double num = 2342344;

  sprintf(line, "*** SPRINTF E *** = %e", num);
  printf("%s\n", line);
  printf("*******MY******** = %s\n", specifierE(num));


    printf("*****%d\n", s21_strlen("1234567.12"));
    printf("*****%d", strlen("1234567.12"));

  return 0;
}