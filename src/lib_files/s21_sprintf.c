#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // DELETE HIM
#include <math.h>

#include "s21_string.h"
#include "s21_utils.h"

typedef struct {
  int64_t d;
  int o;
  int x;
  int X;
  long double f;
  char c;
  char *s;
  unsigned int u;
  int *n;
  int *p;
  double e;
  int E;
} Specifiers_s;

typedef struct {
  int plus;
  int minus;
  int space;
  int null;
  int sharp;
} Flags_s;

typedef struct {
  int number;
} Width_s;

typedef struct {
  int number;
  int isNull;
} Accuracy_s;

typedef struct {
  int h;
  int l;
  int L;
} Length_s;

typedef struct {
  Specifiers_s specifiers;
  Flags_s flags;
  Width_s width;
  Accuracy_s accuracy;
  Length_s length;
  int isNegative;
} Arguments_s;

int s21_sprintf(char* str, const char* format, ...);
void formatStringHandler(char* str, const char* format, Arguments_s* arguments,
                         va_list factor, char* startStr, int *nonPrintCh);
char* specifiersHandler(char* str, const char* ch, Arguments_s* arguments,
                        va_list factor, char* startStr, int *nonPrintCh);

char* diSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* fSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* cSpecifierHandler(char* str, Arguments_s* arguments, va_list factor, int *nonPrintCh);
char* sSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* uSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* oSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* xSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
void nSpecifierHandler(char* str, Arguments_s* arguments, va_list factor,
                       char* startStr);
char* pSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* eSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);

void resetArguments(Arguments_s* arguments);

char* printFormatWithSpaces(char* str, Arguments_s* arguments,
                            const char* string);

char *printSpecificatorD(char* str, Arguments_s* arguments, const char* string);
char *printSpecificatorF(char* str, Arguments_s* arguments, const char* string);
char* printSpecificatorE(char* str, Arguments_s* arguments, const char* string);

const char* flagsHandler(const char* ch, Arguments_s* arguments);
const char* widthHandle(const char* ch, Arguments_s* arguments, va_list factor);
const char* accuracyHandle(const char* ch, Arguments_s* arguments,
                           va_list factor);
const char* lengthHandle(const char* ch, Arguments_s* arguments);

int spacesCounter(Arguments_s* arguments, const char* string);
int nullsCounter(Arguments_s* arguments, const char* string);

char* printSpaces(char* str, int spaces);
char* printNulls(char* str, Arguments_s* arguments, int nulls);

// int main() {
//   char str1[400];
//   char str2[400];
  
  
//   char *str3 = "test: %020f!\ntest: %-020f!\ntest: %+025f!";
//   double num = 837564.4753366;

//   printf("sprintf = %d\n" , sprintf(str1, str3, num, num, num));
//   printf("s21_sprintf = %d\n" ,                 s21_sprintf(str2, str3, num, num, num));
//   // sprintf(str1, str3, val1, strTest, &ch, &valN1, val2, strTest2, val3,
//   //         strTest2, val4, ch, strTest, uVal, val5);
//   // s21_sprintf(str2, str3, val1, strTest, &ch, &valN2, val2, strTest2, val3,
//   //             strTest2, val4, ch, strTest, uVal, val5);
//   // printf("%f!!!!\n", fractionOfE(val5));

//   printf("%s$\n", str1);
//   printf("%s$\n", str2);

//   return 0;
// }

int s21_sprintf(char* str, const char* format, ...) {
  Arguments_s arguments = {0};

  va_list factor;
  va_start(factor, format);
  char *startStr = str;
  int nonPrintCh = 0;

  formatStringHandler(str, format, &arguments, factor, startStr, &nonPrintCh);

  va_end(factor);

  return s21_strlen(startStr) + nonPrintCh;
}

void formatStringHandler(char *str, const char *format, Arguments_s *arguments,
                         va_list factor, char *startStr, int *nonPrintCh) {
  for (const char *ch = format; *ch; ch++) {
    if (*ch != '%') {
      *str++ = *ch;
    } else {
      ch = flagsHandler(ch, arguments);
      ch = widthHandle(ch, arguments, factor);
      ch = accuracyHandle(ch, arguments, factor);
      ch = lengthHandle(ch, arguments);

      str = specifiersHandler(str, ch, arguments, factor, startStr, nonPrintCh);
    }
    resetArguments(arguments);
  }
  *str = '\0';
}

char *specifiersHandler(char *str, const char *ch, Arguments_s *arguments,
                        va_list factor, char *startStr, int *nonPrintCh) {
  switch (*ch) {
    case 'i':
    case 'd':
      str = diSpecifierHandler(str, arguments, factor);
      break;
    case 'f':
      str = fSpecifierHandler(str, arguments, factor);
      break;
    case 'c':
      str = cSpecifierHandler(str, arguments, factor, nonPrintCh);
      break;
    case 's':
      str = sSpecifierHandler(str, arguments, factor);
      break;
    case 'u':
      str = uSpecifierHandler(str, arguments, factor);
      break;
    case 'o':
      str = oSpecifierHandler(str, arguments, factor);
      break;
    case 'X':
      arguments->specifiers.X = 1;
      str = xSpecifierHandler(str, arguments, factor);
      break;
    case 'x':
      //Можно попробовать такой вариант вместо дублирования  
      // if(*ch == 'X') arguments->specifiers.X = 1;
      str = xSpecifierHandler(str, arguments, factor);
      break;
    case 'n':
      nSpecifierHandler(str, arguments, factor, startStr);
      break;
    case 'p':
      str = pSpecifierHandler(str, arguments, factor);
      break;
    case 'E':
      arguments->specifiers.E = 1;
      str = eSpecifierHandler(str, arguments, factor);
      break;
    case 'e':
      //Можно попробовать такой вариант вместо дублирования  
      // if(*ch == 'E') arguments->specifiers.E = 1;
      str = eSpecifierHandler(str, arguments, factor);
      break;
    case '%':
      *str++ = *ch;
      break;
    default:
      break;
  }

  return str;
}

/* Обработка спецификатора %d
str - Форматная строка
arguments - структура различных аргументов аргументов
factor - подаваемое число */
char *diSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  if (arguments->length.h) {
    arguments->specifiers.d = (short)va_arg(factor, int);
  } else if (arguments->length.l) {
    arguments->specifiers.d = (long)va_arg(factor, long int);
  } else {
    arguments->specifiers.d = va_arg(factor, int);
  }

  if(arguments->specifiers.d < 0) {
    arguments->isNegative = 1;
    arguments->specifiers.d *= -1;
  }
  char* dString = intInChar(arguments->specifiers.d);

  str = printSpecificatorD(str, arguments, dString);
  free(dString); 

  return str;
}

// Обработка спецификатора %f
char *fSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  if (!arguments->accuracy.isNull && arguments->accuracy.number == 0) {
    arguments->accuracy.number = 6;
  }
  if (arguments->length.L) {
    arguments->specifiers.f = (long double)va_arg(factor, long double);
  } else {
    arguments->specifiers.f = va_arg(factor, double);
  }
  if(arguments->specifiers.f < 0) {
    arguments->isNegative = 1;
    arguments->specifiers.f *= -1;
  }

  arguments->specifiers.f = roundTo(arguments->specifiers.f, arguments->accuracy.number);
  char* fString = doubleInCharN(arguments->specifiers.f, arguments->accuracy.number);
  if(arguments->flags.sharp && arguments->accuracy.isNull) {
    fString[strlen(fString)] = '.';
  }

  str = printSpecificatorF(str, arguments, fString);
  free(fString);

  return str;
}

// Обработка спецификатора %c
char *cSpecifierHandler(char *str, Arguments_s *arguments, va_list factor, int *nonPrintCh) {
  if (arguments->length.l) {
    arguments->specifiers.c = (wchar_t)va_arg(factor, int);
  } else {
    arguments->specifiers.c = (char)va_arg(factor, int);
  }
  if(arguments->specifiers.c == 0) {
    *nonPrintCh = *nonPrintCh + 1;
  }

  str = printFormatWithSpaces(str, arguments, &(arguments->specifiers.c));

  return str;
}

// Обработка спецификатора %s
char *sSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  arguments->specifiers.s = (char *)va_arg(factor, char *);
  if (!arguments->accuracy.number && !arguments->accuracy.isNull) {
    arguments->accuracy.number = s21_strlen(arguments->specifiers.s);
  }

  str = printFormatWithSpaces(str, arguments, arguments->specifiers.s);

  return str;
}

// Обработка спецификатора %u
char *uSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  if (arguments->length.h) {
    arguments->specifiers.u = (unsigned short)va_arg(factor, unsigned int);
  } else if (arguments->length.l) {
    arguments->specifiers.u = (unsigned long)va_arg(factor, unsigned int);
  } else {
    arguments->specifiers.u = va_arg(factor, unsigned int);
  }
  char *uString = intInChar(arguments->specifiers.u);
  str = printFormatWithSpaces(str, arguments, uString);

  free(uString);

  return str;
}

// Обработка спецификатора %o
char *oSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  if (arguments->length.h) {
    arguments->specifiers.o = (short)va_arg(factor, int);
  } else if (arguments->length.l) {
    arguments->specifiers.o = (long)va_arg(factor, int);
  } else {
    arguments->specifiers.o = va_arg(factor, int);
  }

  char *oString = octaIntInChar(arguments->specifiers.o);

  if (arguments->flags.plus && arguments->specifiers.o > 0 &&
      !arguments->flags.sharp) {
    *str++ = '+';
  }
  if (arguments->flags.space && arguments->specifiers.o > 0 &&
      !arguments->flags.sharp) {
    *str++ = ' ';
  }

  str = printFormatWithSpaces(str, arguments, oString);

  free(oString);
  return str;
}

char *xSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  if (arguments->length.h) {
    arguments->specifiers.x = (short)va_arg(factor, int);
  } else if (arguments->length.l) {
    arguments->specifiers.x = (long)va_arg(factor, int);
  } else {
    arguments->specifiers.x = va_arg(factor, int);
  }
  char *xString = hexaIntInChar(arguments->specifiers.x);
  if (arguments->specifiers.X) {
    xString = s21_to_upper(xString);
  }
  if (arguments->flags.plus && arguments->specifiers.x > 0) {
    *str++ = '+';
  }
  if (arguments->flags.space && arguments->specifiers.x > 0) {
    *str++ = ' ';
  }

  str = printFormatWithSpaces(str, arguments, xString);

  free(xString);
  return str;
}

void nSpecifierHandler(char *str, Arguments_s *arguments, va_list factor,
                       char *startStr) {
  arguments->specifiers.n = va_arg(factor, int *);
  int value = str - startStr;

  *arguments->specifiers.n = value;
}

char *pSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  arguments->specifiers.p = va_arg(factor, int *);
  int *p = arguments->specifiers.p;
  char *pString = ptrInChar(p);

  str = printFormatWithSpaces(str, arguments, pString);

  return str;
}

char *eSpecifierHandler(char *str, Arguments_s *arguments, va_list factor) {
  if (!arguments->accuracy.isNull && arguments->accuracy.number == 0) {
    arguments->accuracy.number = 6;
  }
  if (arguments->length.L) {
    arguments->specifiers.e = (long double)va_arg(factor, double);
  } else {
    arguments->specifiers.e = va_arg(factor, double);
  }
  double fraction;
  if (arguments->accuracy.isNull) {
    fraction = floor(fractionOfE(arguments->specifiers.e));
  } else {
    fraction = fractionOfE(arguments->specifiers.e);
  }
  char *fractionStr = doubleInChar(fraction);

  char *eString = malloc(sizeof(char));
  if (eString == S21_NULL) {
    printError(errno);
    exit(1);
  }
  int i = 0;
  while (*fractionStr) {
    eString = realloc(eString, sizeof(char) * (i + 3));
    *(eString + i) = *fractionStr++;
    i++;
  }

  char *exponent = exponentOfE(arguments->specifiers.e);

  while (*exponent) {
    eString = realloc(eString, sizeof(char) * (i + 3) * 2);
    *(eString + i) = *exponent++;
    i++;
  }
  *(eString + i) = '\0';

  free(exponent);
  free(fractionStr);

  if (arguments->specifiers.E) {
    eString = s21_to_upper(eString);
  }
  if (arguments->flags.plus && arguments->specifiers.e > 0) {
    *str++ = '+';
  }
  if (arguments->flags.space && arguments->specifiers.e > 0) {
    *str++ = ' ';
  }

  str = printFormatWithSpaces(str, arguments, eString);
  free(eString);

  return str;
}

const char *flagsHandler(const char *ch, Arguments_s *arguments) {
  ch = ch + 1;
  while (*ch == '-' || *ch == '+' || *ch == ' ' || *ch == '0' || *ch == '#') {
    switch (*ch) {
    case '-':
      arguments->flags.minus = 1;
      ch = ch + 1;
      break;
    case '+':
      arguments->flags.plus = 1;
      arguments->flags.space = 0;
      ch = ch + 1;
      break;
    case ' ':
      if (!(arguments->flags.plus)) {
        arguments->flags.space = 1;
      }
      ch = ch + 1;
      break;
    case '0':
      arguments->flags.null = 1;
      ch = ch + 1;
      break;
    case '#':
      arguments->flags.sharp = 1;
      ch = ch + 1;
      break;
    default:
      break;
    }
  }

  return ch;
}

void resetArguments(Arguments_s *arguments) {
  s21_memset(arguments, 0, sizeof(Arguments_s));
}

const char *widthHandle(const char *ch, Arguments_s *arguments,
                        va_list factor) {
  while (*ch >= '0' && *ch <= '9') {
    if (arguments->width.number == 0) {
      arguments->width.number = strInInt(*ch);
    } else {
      arguments->width.number = arguments->width.number * 10 + strInInt(*ch);
    }
    ch = ch + 1;
  }

  if (*ch == '*') {
    arguments->width.number = va_arg(factor, int);
    ch = ch + 1;
  }

  return ch;
}

char *printFormatWithSpaces(char *str, Arguments_s *arguments,
                            const char *string) {
  int spaces = spacesCounter(arguments, string);
  int nulls = nullsCounter(arguments, string);
  spaces = spaces - nulls;

  if ((arguments->width.number && !arguments->flags.minus) ||
      arguments->accuracy.number /* && !arguments->specifiers.d */) {
    str = printSpaces(str, spaces);
    if (!arguments->specifiers.f && !arguments->specifiers.e) {
      str = printNulls(str, arguments, nulls);
    } else if ((arguments->specifiers.f || arguments->specifiers.e) && arguments->width.number) {
      str = printNulls(str, arguments, nulls);
    }
  }

  if (arguments->flags.sharp &&
      (arguments->specifiers.o || arguments->specifiers.x)) {
    *str++ = '0';
    if (arguments->specifiers.X) {
      *str++ = 'X';
    } else if (arguments->specifiers.x) {
      *str++ = 'x';
    }
  }

  // Проверяем если точность != 0 и значение != 0
  if (!(arguments->accuracy.isNull &&
        (arguments->specifiers.d == 0 && arguments->specifiers.o == 0 &&
         arguments->specifiers.u == 0 && arguments->specifiers.x == 0 &&
         arguments->specifiers.X == 0)) &&
      !arguments->specifiers.e &&
      (!arguments->specifiers.s || arguments->specifiers.p)) {
    // то добавляем в строку
    while (*string) {
      *str++ = *string++;
    }
  }
  if (arguments->specifiers.f && arguments->accuracy.isNull) {
    while (*string && *string != '.') {
      *str++ = *string++;
    }
  }
  // Строку печатаем полностью или если задана точность, то определенное количество символов
  if (arguments->specifiers.s) {
    while (*string && arguments->accuracy.number &&
           !arguments->accuracy.isNull) {
      *str++ = *string++;
      arguments->accuracy.number--;
    }
  }
  if (arguments->specifiers.e) {
    str = printSpecificatorE(str, arguments, string);
  }
  if (arguments->width.number && arguments->flags.minus) {
    str = printSpaces(str, spaces);
  }
  if (arguments->specifiers.f) {
    str = printNulls(str, arguments, nulls);
  }

  return str;
}

char *printSpecificatorD(char* str, Arguments_s* arguments, const char* string) {
  int spaces = spacesCounter(arguments, string);
  if (arguments->accuracy.isNull && arguments->specifiers.d == 0) {
    spaces++;
  }
  int nulls = nullsCounter(arguments, string);
  spaces = spaces - nulls;
  if (!arguments->flags.minus) {
    if (arguments->width.number || arguments->accuracy.number) {
      str = printSpaces(str, spaces);
    }
  }

  if (arguments->flags.plus && !arguments->isNegative) {
    *str++ = '+';
  }
  if (arguments->flags.space && !arguments->isNegative) {
    *str++ = ' ';
  }

  

  if(arguments->isNegative) {
    *str++ = '-';
  }

  if ((arguments->width.number && !arguments->flags.minus) || arguments->accuracy.number) {    
    str = printNulls(str, arguments, nulls);
  }

  // Проверяем если точность != 0 и значение != 0
  if (!(arguments->accuracy.isNull && arguments->specifiers.d == 0)) {
    // то добавляем в строку

    while (*string) {
      *str++ = *string++;
    }
  }

  if (arguments->width.number && arguments->flags.minus) {
    str = printSpaces(str, spaces);
  }

  return str;
}

char *printSpecificatorF(char *str, Arguments_s *arguments,
                         const char *string) {
  int isAfterComma = 0;
  int spaces = spacesCounter(arguments, string);
  int nulls = nullsCounter(arguments, string);
  
  spaces = spaces - nulls;
  // printf("spaces = %d, nulls = %d, string = %s\n", spaces, nulls, string);

  if (!arguments->flags.minus && !arguments->flags.null) {
    // if (arguments->width.number && arguments->accuracy.number) {  // test sprintf_1_f
      str = printSpaces(str, spaces);
    // }
  }

  if (arguments->flags.plus && !arguments->isNegative) {
    *str++ = '+';
  }
  if (arguments->flags.space && !arguments->isNegative) {
    *str++ = ' ';
  }

  if (arguments->isNegative) {
    *str++ = '-';
  }

  if (arguments->width.number && arguments->flags.null && !arguments->flags.minus) {
    str = printNulls(str, arguments, spaces);
  }

  while (*string &&
         (arguments->accuracy.number > 0 || arguments->accuracy.isNull)) {
    if (isAfterComma == 1) {
      arguments->accuracy.number--;
    }

    if (*string == '.') {
      isAfterComma = 1;
      if (arguments->flags.sharp && arguments->accuracy.isNull) {
        arguments->accuracy.number = -1;
        arguments->accuracy.isNull = 0;
      }
    }
    if (!arguments->flags.sharp && arguments->accuracy.isNull &&
        *string == '.') {
      string = string + 1;
      arguments->accuracy.number = -1;
      arguments->accuracy.isNull = 0;
    } else {
      *str++ = *string++;
    }
  }

  if (arguments->width.number && arguments->flags.minus) {
    str = printSpaces(str, spaces);
  }

  str = printNulls(str, arguments, nulls);

  return str;
}

char *printSpecificatorE(char *str, Arguments_s *arguments,
                         const char *string) {
  int isAfterComma = 0;

  while (*string &&
         (arguments->accuracy.number > 0 || arguments->accuracy.isNull) &&
         !(*string == 'e' || *string == 'E')) {
    if (isAfterComma == 1) {
      arguments->accuracy.number--;
    }
    
    if (*string == '.') {
      isAfterComma = 1;
      if(arguments->flags.sharp && arguments->accuracy.isNull) {
        arguments->accuracy.number = -1;
        arguments->accuracy.isNull = 0;
      }
    }
    if(!arguments->flags.sharp && arguments->accuracy.isNull && *string == '.') {
      string = string + 1;
      arguments->accuracy.number = -1;
      arguments->accuracy.isNull = 0;
    }else {
      *str++ = *string++;
    }
    
  }
  str = printNulls(str, arguments, arguments->accuracy.number);

  while (*string && !(*string == 'e' || *string == 'E')) {
    string = string + 1;
  }
  while (*string) {
    *str++ = *string++;
  }

  return str;
}

const char *accuracyHandle(const char *ch, Arguments_s *arguments,
                           va_list factor) {
  if (*ch == '.') {
    ch = ch + 1;
    // Если после точки идет 0 или сразу спецификатор
    if ((*ch == '0' || *ch > '9') && arguments->accuracy.number == 0) {
      arguments->accuracy.isNull = 1;
      // #####################################################
      return *ch == '0' ? ++ch : ch;  // Нужно попробовать поменять !!!!!!!!!!!!
      // #####################################################
    }
    // Смотрим значение точности
    while (*ch >= '0' && *ch <= '9') {
      if (arguments->accuracy.number == 0) {
        arguments->accuracy.number = strInInt(*ch);
      } else {
        arguments->accuracy.number =
            arguments->accuracy.number * 10 + strInInt(*ch);
      }
      ch = ch + 1;
    }

    if (*ch == '*') {
      arguments->accuracy.number = va_arg(factor, int);
      ch = ch + 1;
    }
  }

  return ch;
}

const char *lengthHandle(const char *ch, Arguments_s *arguments) {
  switch (*ch) {
    case 'h':
      arguments->length.h = 1;
      ch = ch + 1;
      break;
    case 'l':
      arguments->length.l = 1;
      ch = ch + 1;
      break;
    case 'L':
      arguments->length.L = 1;
      ch = ch + 1;
      break;
    default:
      break;
  }

  return ch;
}

int spacesCounter(Arguments_s *arguments, const char *string) {
  int spaces = 0;
  const char *ptr = string;
  if (arguments->width.number && !arguments->flags.null) {
    spaces = arguments->width.number - s21_strlen(ptr);
  }

  if (arguments->flags.sharp &&
      (arguments->specifiers.o || arguments->specifiers.x)) {
    spaces--;
    if (arguments->specifiers.x) {
      spaces--;
    }
  }

  if (arguments->specifiers.f) {
    spaces = arguments->width.number - (s21_strcspn(string, ".") + arguments->accuracy.number + 1);
    if(arguments->accuracy.isNull && !arguments->flags.sharp) {
      spaces++;
    }
  }

  if (arguments->isNegative) {
    spaces--;
  } else {
    if (arguments->flags.space || arguments->flags.plus) {
      spaces--;
    }
  }


  return spaces;
}

int nullsCounter(Arguments_s *arguments, const char *string) {
  int nulls = 0;
  if (arguments->width.number && !arguments->flags.minus &&
      arguments->flags.null && !arguments->accuracy.number) {
    nulls = arguments->width.number - s21_strlen(string);
  } else if (arguments->accuracy.number) {
    nulls = arguments->accuracy.number - s21_strlen(string);
  }

  // if(arguments->specifiers.f || arguments->specifiers.e) {
  //   nulls = arguments->accuracy.number - (s21_strlen(s21_strchr(string, '.')));
  // }

  if(arguments->isNegative && !arguments->accuracy.number) {
    nulls--;
  }

  return nulls > 0 ? nulls : 0;
}

char *printSpaces(char *str, int spaces) {
  while (spaces > 0) {
    *str++ = ' ';
    spaces--;
  }

  return str;
}

char *printNulls(char *str, Arguments_s *arguments, int nulls) {
  while (nulls > 0 && (arguments->flags.null || arguments->accuracy.number)) {
    *str++ = '0';
    nulls--;
  }

  return str;
}
