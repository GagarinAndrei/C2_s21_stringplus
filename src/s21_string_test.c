#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s21_string.h"

int main() {

//     START_TEST (test_name)
// {
//   /* unit test code */
// }
// END_TEST
    char text[50] = "Hello World";
    char text2[50] = "He";

    char *res;
    char *s21_res;

    printf("%s - strchr\n", strchr(text, 'o'));
    printf("%s - s21_strchr\n", s21_strchr(text, 'o'));
    printf("\n------------------------------\n\n");

    res = memchr(text, 'o', 6);
    s21_res = s21_memchr(text, 'o', 6);

    printf("%s - memchr\n", res);
    printf("%s - s21_memchr\n", s21_res);
    printf("\n------------------------------\n\n");

    printf("%s - strpbrk\n", strpbrk(text, text2));
    printf("%s - s21_strpbrk\n", s21_strpbrk(text, text2));
    printf("\n------------------------------\n\n");

    printf("%s - strpbrk\n", strrchr(text, 'o'));
    printf("%s - s21_strpbrk\n", s21_strrchr(text, 'o'));
    printf("\n------------------------------\n\n");

    printf("%s - strstr\n", strstr(text, text2));
    printf("%s - s21_strstr\n", s21_strstr(text, text2));
    printf("\n------------------------------\n\n");

    printf("%d - memcmp\n", memcmp(text, text2, 5));
    printf("%d - s21_memcmp\n", s21_memcmp(text, text2, 5));
    printf("\n------------------------------\n\n");

    printf("%d - strncmp\n", strncmp(text, text2, 5));
    printf("%d - s21_strncmp\n", s21_strncmp(text, text2, 5));
    printf("\n------------------------------\n\n");

    strncat(text, text2, 1);
    printf("%s - strncat\n", text);
    s21_strncat(text, text2, 1);
    printf("%s - s21_strncat\n", text);
    printf("\n------------------------------\n\n");

    return 0;
}
