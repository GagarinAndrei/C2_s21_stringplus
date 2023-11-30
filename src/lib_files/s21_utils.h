#ifndef S21_UTILS_H
#define S21_UTILS_H

int formatCounter(const char* string);

int digitsInIntCounter(long long n);
char* intInChar(long long number);

char* doubleInChar(long double number);
char *doubleInCharN(long double number, unsigned short n);
int numberAfterComma(double n);

int strInInt(char ch);

char* conversionDexInHexOrOcta(int number, int numeralSystem);

char* octaIntInChar(int number);
char* hexaIntInChar(int number);

char* reverseStr(char* str);
char* ptrInChar(int* ptr);

char* exponentInStr(double number);
double fractionOfE(double number);
int exponent(double number);
char* exponentOfE(double number);
void printError(int error);
long double roundTo(long double Number, short Precision);

#endif