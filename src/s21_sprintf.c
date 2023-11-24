#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // DELETE HIM

#include "lib_files/s21_string.h"

#include "s21_utils.h"

typedef struct {
  int d;
  int o;
  int x;
  int X;
  double f;
  char c;
  char* s;
  unsigned int u;
  int* n;
  int* p;
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
} Arguments_s;

int s21_sprintf(char *str, const char *format, ...);
void formatStringHandler(char* str, const char* format, Arguments_s* arguments, va_list factor, char* startStr);

char* diSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* fSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* cSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* sSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* uSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* oSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
char* xSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);
void nSpecifierHandler(char* str, Arguments_s* arguments, va_list factor, char* startStr);
char* pSpecifierHandler(char* str, Arguments_s* arguments, va_list factor);

const char* flagsHandler(const char* ch, Arguments_s* arguments);
void resetArguments(Arguments_s* arguments);

const char* widthHandle(const char* ch, Arguments_s* arguments, va_list factor);
int spacesCounter(Arguments_s* arguments, const char* string);
char* printSpaces(char* str, Arguments_s* arguments, int spaces);
char* printNulls(char* str, Arguments_s* arguments, int nulls);
char* printFormatWithSpaces(char* str, Arguments_s* arguments, const char* string);

const char* accuracyHandle(const char* ch, Arguments_s* arguments, va_list factor);
const char* lengthHandle(const char* ch, Arguments_s* arguments);

char* octaIntInChar(int number);
char* hexaIntInChar(int number);

int main() {
    char str1[1000];
    char str2[1000];
    char strTest[] = "Test";
    char strTest2[] = "StringS!";
    // char *str3 = "%d %s free %.p %n %X %s % d %s %d %.10c %.13s %u %%TFR %20.4f ";
    char *str3 = "&%e&";
    unsigned int val1 = 32767 * 4096 * 16 + 65535;
    int val2 = 255;
    int val3 = 3231;
    int val4 = 6;
    double val5 = 1567312.1400000000000014;
    unsigned int uVal = 1808867574;
    char ch = 'Q';
    int valN1 = 0;
    int valN2 = 0;
     
     sprintf(str1, str3,  val5);
    //  s21_sprintf(str2, str3, val5 );
    // sprintf(str1, str3, val1, strTest, &ch, &valN1, val2, strTest2, val3, strTest2, val4, ch, strTest, uVal, val5);
    // s21_sprintf(str2, str3, val1, strTest, &ch, &valN2, val2, strTest2, val3, strTest2, val4, ch, strTest, uVal, val5);

    printf("%s$\n", str1);
    printf("%s$\n", str2);
    // printf("%d$\n", valN1);
    // printf("%d$\n", valN2);

    return 0;
}

int s21_sprintf(char* str, const char *format, ...) {
  Arguments_s arguments = {0};

  va_list factor;
  va_start(factor, format);
  char* startStr = str;

  formatStringHandler(str, format, &arguments, factor, startStr);

  va_end(factor);

  return 0;
}

void formatStringHandler(char* str, const char* format, Arguments_s* arguments,
                         va_list factor, char* startStr) {
  for (const char* ch = format; *ch; ch++) {
    if (*ch != '%') {
      *str++ = *ch;
    } else {
      ch = flagsHandler(ch, arguments);
      ch = widthHandle(ch, arguments, factor);
      ch = accuracyHandle(ch, arguments, factor);
      ch = lengthHandle(ch, arguments);
      
      switch (*ch) {
      case 'i':
      case 'd':
        str = diSpecifierHandler(str, arguments, factor);
        break;
      case 'f':
        str = fSpecifierHandler(str, arguments, factor);
        break;
      case 'c':
        str = cSpecifierHandler(str, arguments, factor);
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
      case 'x':
        str = xSpecifierHandler(str, arguments, factor);
        break;
      case 'n':
        nSpecifierHandler(str, arguments, factor, startStr);
        break;
      case 'p':
        str = pSpecifierHandler(str, arguments, factor);
        break;
      case 'e':
        str = eSpecifierHandler(str, arguments, factor);
        break;
      case '%':
        *str++ = *ch;
        break;
      default:
        break;
      }
    }
    resetArguments(arguments);
  }
  *str = '\0';
}

/* Обработка спецификатора %d
str - Форматная строка
arguments - структура различных аргументов аргументов
factor - подаваемое число */
char* diSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  if(arguments->length.h) {
    arguments->specifiers.d = (short)va_arg(factor, int);
  } else if (arguments->length.l) {
    arguments->specifiers.d = (long)va_arg(factor, int);
  } else {
    arguments->specifiers.d = va_arg(factor, int);
  }
  char* dString = intInChar(arguments->specifiers.d);

  if (arguments->flags.plus && arguments->specifiers.d > 0) {
    *str++ = '+';
  }
  if (arguments->flags.space && arguments->specifiers.d > 0) {
    *str++ = ' ';
  }
  str = printFormatWithSpaces(str, arguments, dString);

  return str;
}

// Обработка спецификатора %f
char* fSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  if(!arguments->accuracy.isNull && arguments->accuracy.number == 0) {
    arguments->accuracy.number = 6;
  }
  if(arguments->length.L) {
    arguments->specifiers.f = (long double)va_arg(factor, double);
  } else {
    arguments->specifiers.f = va_arg(factor, double);
  }
  char* fString = doubleInChar(arguments->specifiers.f);
  int spaces = spacesCounter(arguments, fString);

  if (arguments->flags.plus && arguments->specifiers.f > 0) {
    *str++ = '+';
  }
  if (arguments->flags.space && arguments->specifiers.f > 0) {
    *str++ = ' ';
  }

  str = printFormatWithSpaces(str, arguments, fString); 

  return str;
}

// Обработка спецификатора %c
char* cSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  if(arguments->length.l) {
    arguments->specifiers.c = (wchar_t)va_arg(factor, int);
  } else {
    arguments->specifiers.c = (char)va_arg(factor, int);
  }
  str = printFormatWithSpaces(str, arguments, &(arguments->specifiers.c));

  return str;
}

// Обработка спецификатора %s
char* sSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  arguments->specifiers.s = (char*)va_arg(factor, char*);
  if(!arguments->accuracy.number && !arguments->accuracy.isNull) {
    arguments->accuracy.number = s21_strlen(arguments->specifiers.s);
  }

  str = printFormatWithSpaces(str, arguments, arguments->specifiers.s);

  return str;
}

// Обработка спецификатора %u
char* uSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  if(arguments->length.h) {
    arguments->specifiers.u = (unsigned short)va_arg(factor, unsigned int);
  } else if(arguments->length.l) {
    arguments->specifiers.u = (unsigned long)va_arg(factor, unsigned int);
  } else {
    arguments->specifiers.u = va_arg(factor, unsigned int);
  }
  char* uString = intInChar(arguments->specifiers.u);
  str = printFormatWithSpaces(str, arguments, uString);

  return str;
}

// Обработка спецификатора %o
char* oSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  if(arguments->length.h) {
    arguments->specifiers.o = (short)va_arg(factor, int);
  } else if (arguments->length.l) {
    arguments->specifiers.o = (long)va_arg(factor, int);
  } else {
    arguments->specifiers.o = va_arg(factor, int);
  }
  
  char *oString = octaIntInChar(arguments->specifiers.o);
  
  if(arguments->flags.plus && arguments->specifiers.o > 0 && !arguments->flags.sharp) {
    *str++ = '+';
  }
  if(arguments->flags.space && arguments->specifiers.o > 0 && !arguments->flags.sharp) {
    *str++ = ' ';
  }

  str = printFormatWithSpaces(str, arguments, oString);

  return str;
}

char* xSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  if(arguments->length.h) {
    arguments->specifiers.x = (short)va_arg(factor, int);
  } else if (arguments->length.l) {
    arguments->specifiers.x = (long)va_arg(factor, int);
  } else {
    arguments->specifiers.x = va_arg(factor, int);
  }
  char *xString = hexaIntInChar(arguments->specifiers.x);
  if(arguments->specifiers.X) {
    xString = s21_to_upper(xString); 
  }
  if(arguments->flags.plus && arguments->specifiers.x > 0) {
    *str++ = '+';
  }
  if(arguments->flags.space && arguments->specifiers.x > 0) {
    *str++ = ' ';
  }

  str = printFormatWithSpaces(str, arguments, xString);

  return str;
}

void nSpecifierHandler(char* str, Arguments_s* arguments, va_list factor, char* startStr) {
  arguments->specifiers.n = va_arg(factor, int*);
  int value = str - startStr;

  *arguments->specifiers.n = value;
}

char* pSpecifierHandler(char* str, Arguments_s* arguments, va_list factor) {
  arguments->specifiers.p = va_arg(factor, int*);
  int *p = arguments->specifiers.p;
  char *pString = ptrInChar(p);
  
  str = printFormatWithSpaces(str, arguments, pString);

  return str;
}

const char* flagsHandler(const char* ch, Arguments_s* arguments) {
  
  *ch++;
  while(*ch == '-' || *ch == '+' || *ch == ' ' || *ch == '0' || *ch == '#') {
    switch (*ch) {
    case '-':
      arguments->flags.minus = 1;
      *ch++;
      break;
    case '+':
      arguments->flags.plus = 1;
      arguments->flags.space = 0; 
      *ch++;
      break;
    case ' ':
      if(!(arguments->flags.plus)) {
        arguments->flags.space = 1;
        *ch++;
      }
      break;
    case '0':
      arguments->flags.null = 1;
      *ch++;
    case '#':
      arguments->flags.sharp = 1;
      *ch++;
      break;
    default:
      break;
    }
  }


  return ch;
}

void resetArguments(Arguments_s* arguments) {
  s21_memset(arguments, 0, sizeof(Arguments_s));
}

const char* widthHandle(const char* ch, Arguments_s* arguments, va_list factor) {
  while(*ch >= '0' && *ch <= '9') {
    if(arguments->width.number == 0) {
      arguments->width.number = strInInt(*ch);
    } else {
      arguments->width.number = arguments->width.number * 10 + strInInt(*ch);
    }
    *ch++;
  }

  if(*ch == '*') {
    arguments->width.number = va_arg(factor, int);
    *ch++;
  }

  return ch;
}

int spacesCounter(Arguments_s* arguments, const char* string) {
  int spaces = 0;
  const char* ptr = string;
  if(arguments->width.number) {
    spaces = arguments->width.number - s21_strlen(ptr); 
  }

  if(arguments->flags.sharp && arguments->specifiers.o || arguments->specifiers.x) {
    spaces--;
    if(arguments->specifiers.x) {
      spaces--;
    }
  }
  
  return spaces;
}

int nullsCounter(Arguments_s* arguments, const char* string) {
  int nulls = 0;
  if(arguments->width.number && !arguments->flags.minus && arguments->flags.null && !arguments->accuracy.number) {
    nulls = arguments->width.number - s21_strlen(string);
  } else if(arguments->accuracy.number) {
    nulls = arguments->accuracy.number - s21_strlen(string);
  }

  if(arguments->specifiers.f) {
    nulls = arguments->accuracy.number - (s21_strlen(s21_strchr(string, '.')) - 1);
  }

  return nulls;
}

char* printFormatWithSpaces(char* str, Arguments_s* arguments, const char* string) {
  int spaces = spacesCounter(arguments, string);
  int nulls = nullsCounter(arguments, string);
  spaces = spaces - nulls;

  if(arguments->width.number && !arguments->flags.minus || arguments->accuracy.number /* && !arguments->specifiers.d */) {
    str = printSpaces(str, arguments, spaces);
    if(!arguments->specifiers.f) {
      str = printNulls(str, arguments, nulls);
    }
  }

  if(arguments->flags.sharp && arguments->specifiers.o || arguments->specifiers.x) {
    *str++ = '0';
    if(arguments->specifiers.X) {
      *str++ = 'X';
    } else if(arguments->specifiers.x) {
      *str++ = 'x';
    }
  }

  // Проверяем если точность != 0 и значение != 0
  if(!(arguments->accuracy.isNull && (arguments->specifiers.d == 0 && arguments->specifiers.o == 0 && arguments->specifiers.u == 0 && arguments->specifiers.x == 0 && arguments->specifiers.X == 0)) && !arguments->specifiers.s || arguments->specifiers.p) {
    // то добавляем в строку
    while(*string) {
      *str++ = *string++;
    }
  } 
  // Строку печатаем полностью или если задана точность, то определенное количество символов
  if (arguments->specifiers.s) {
    while(*string && arguments->accuracy.number && !arguments->accuracy.isNull) {
      *str++ = *string++;
      arguments->accuracy.number--;
    }
  }

  if(arguments->width.number && arguments->flags.minus) {
    str = printSpaces(str, arguments, spaces);
  }
  if(arguments->specifiers.f) {
    str = printNulls(str, arguments, nulls);
  }

  return str;
}

const char* accuracyHandle(const char* ch, Arguments_s* arguments, va_list factor) {
  if(*ch == '.') {
    *ch++;
    // Если после точки идет 0 или сразу спецификатор 
    if((*ch == '0' || *ch > '9') && arguments->accuracy.number == 0) {
      arguments->accuracy.isNull = 1;
      // #####################################################
      return *ch == '0' ? ++ch : ch; //Нужно попробовать поменять !!!!!!!!!!!!
      // #####################################################
    }
    // Смотрим значение точности
    while(*ch >= '0' && *ch <= '9') {
      if(arguments->accuracy.number == 0) {
        arguments->accuracy.number = strInInt(*ch);
      } else {
        arguments->accuracy.number = arguments->accuracy.number * 10 + strInInt(*ch);
      }
      *ch++;
    }

    if(*ch == '*') {
      arguments->accuracy.number = va_arg(factor, int);
      *ch++;
    }
  }

  return ch;
}

const char* lengthHandle(const char* ch, Arguments_s* arguments) {
  switch (*ch)
  {
  case 'h':
    arguments->length.h = 1;
    *ch++;
    break;
  case 'l':
    arguments->length.l = 1;
    *ch++;
    break;
  case 'L':
    arguments->length.L = 1;
    *ch++;
    break;
  default:
    break;
  }

  return ch;
}

char* printSpaces(char* str, Arguments_s* arguments, int spaces) {
  while(spaces > 0) {
      *str++ = ' ';
      spaces--;
  }

  return str;
}

char* printNulls(char* str, Arguments_s* arguments, int nulls) {
  while(nulls > 0 && (arguments->flags.null || arguments->accuracy.number)) {
      *str++ = '0';
      nulls--;
  }

  return str;
}
