#include "s21_string.h"

#define NULL ((void*)0)

s21_size_t s21_strlen(const char *str) {
	s21_size_t length = 0;
		while (*str != '\0') {
			length++;
			str++;
		}
	return length;
}

char *s21_strchr(const char *str, int c) {
	int i = 0;
    while (str[i] && str[i] != c) {
		++i;
	}
    return c == str[i] ? (char*)str + i : NULL;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
	s21_size_t i = 0;
    while (*((char*)str + i) && *((char*)str + i) != c && i < n) {
		++i;
	}
    return c == *((char*)str + i)? (char*)str + i : NULL;
}

char *s21_strpbrk(const char *str1, const char *str2) {
	int i = 0, j = 0;
	char c = 0;
	while(str1[i]) {
		c = str1[i];
		while (str2[j] && str2[j] != c) {
			++j;
		}
    	if( c == str2[j]) {
			return (char*)str1 + i;
		}
		j = 0;
		++i;
	}
	return NULL;
}

char *s21_strrchr(const char *str, int c) {
	int i = 0;
	int j = 0;
    while (str[i]) {
		if(str[i] == c) {
			j = i;
		}
		++i;
	}
    return c == str[j] ? (char*)str + j : NULL;
}

int compare(const char *x, const char *y) {
	int returnCode = 1;
	
    while (*x && *y) {
        if (*x != *y) {
            returnCode = 0;
        }
 
        x++;
        y++;
    }

    return returnCode;
}
 
const char* s21_strstr(const char* haystack, const char* needle) {
    while (*haystack != '\0') {
        if (*haystack == *needle && compare(haystack, needle)) {
           return haystack;
        }
        haystack++;
    }
 
    return NULL;
}