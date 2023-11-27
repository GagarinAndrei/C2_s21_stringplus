#ifndef S21_UTILS_H
#define S21_UTILS_H

int formatCounter(const char* string);

int digitsInIntCounter(int n);
char* intInChar(int number);

char* doubleInChar(double number);
int numberAfterComma(double n);

int strInInt(char ch);

char* conversionDexInHexOrOcta(int number, int numeralSystem);

char* octaIntInChar(int number);
char* hexaIntInChar(int number);

char* reverseStr(char *str);
char* ptrInChar(int* ptr);

char* exponentInStr(double number);
double fractionOfE(double number);
int exponent(double number);
char* exponentOfE(double number);
void printError(int error);
double roundTo(double Number, short Precision);

#endif