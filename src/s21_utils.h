#ifndef S21_UTILS_H
#define S21_UTILS_H


int formatCounter(const char* string);

int digitsInIntCounter(int n);
char* intInChar(int number);

char* doubleInChar(double number);
int numberAfterComma(double n);

int strInInt(char ch);

char* conversionDexInHexOrOcta(int number, int numeralSystem);

void printError(int error);

#endif