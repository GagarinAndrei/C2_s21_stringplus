#ifndef SRC_TESTS_ME_H
#define SRC_TESTS_ME_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../lib_files/s21_string.h"

Suite *test_memchr(void);    // 1
Suite *test_memcmp(void);    // 2
Suite *test_memcpy(void);    // 3
Suite *test_memset(void);    // 4
Suite *test_strncat(void);   // 5
Suite *test_strchr(void);    // 6
Suite *test_strncmp(void);   // 7
Suite *test_strncpy(void);   // 8
Suite *test_strcspn(void);   // 9
Suite *test_strerror(void);  // 10
Suite *test_strlen(void);    // 11
Suite *test_strpbrk(void);   // 12
Suite *test_strrchr(void);   // 13
Suite *test_strstr(void);    // 14
Suite *test_strtok(void);    // 15
Suite *test_strspn(void);    // 16
Suite *test_to_lower(void);
Suite *test_to_upper(void);
Suite *test_trim(void);
Suite *test_insert(void);

#endif  // SRC_TESTS_ME_H
