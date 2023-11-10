# all, clean, test, s21_string.a, gcov_report

GCC=gcc
CFALGS=-Wall -Werror -Wextra -std=c11

all: clean s21_string.a 

s21_string.a:
	$(GCC) $(CFALGS) s21_string_test.c s21_string.c s21_memset.c s21_memcpy.c s21_strncpy.c -o s21_string

test:
	./s21_string

gcov_report:


clean:
	rm -f s21_string