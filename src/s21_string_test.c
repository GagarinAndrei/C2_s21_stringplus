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
    char text[] = "Hello World";
    char text2[] = "lo";

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

    return 0;
}
