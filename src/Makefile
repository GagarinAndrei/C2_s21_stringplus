# all, clean, test, s21_string.a, gcov_report

GCC=gcc
CFALGS=-Wall -Werror -Wextra -std=c11
SOURCES=*.c
TESTS_SOURCES=tests/test_me.c tests/test_memchr.c tests/test_memcmp.c tests/test_memcpy.c tests/test_memset.c tests/test_strncat.c tests/test_strchr.c tests/test_strncmp.c tests/test_strncpy.c tests/test_strcspn.c tests/test_strerror.c tests/test_strlen.c tests/test_strpbrk.c tests/test_strrchr.c tests/test_strstr.c tests/test_strtok.c tests/test_strspn.c tests/test_to_lower.c tests/test_to_upper.c tests/test_trim.c tests/test_insert.c
OBJECTS=$(SOURCES:.c=.o)

ifeq ($(OS), Linux)
	CHECKFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
	CHECKFLAGS=-lcheck -lm -lpthread
endif

all: clean s21_string.a 

s21_string.a:
	$(GCC) $(CFALGS) lib_files/$(SOURCES) -c 
	ar rc libs21_string.a $(OBJECTS)
	ranlib libs21_string.a

test: clean s21_string.a
#	$(GCC) $(CFALGS) -L. -ls21_string $(CHECKFLAGS) -o s21_string
	$(GCC) $(CFALGS) $(TESTS_SOURCES) -L. -ls21_string $(CHECKFLAGS) -o s21_string
	./s21_string
# удалить использование библиотеки check

gcov_report: clean s21_string.a
	$(GCC) $(CFALGS) $(TESTS_SOURCES) -L. -ls21_string $(CHECKFLAGS) -fprofile-arcs -ftest-coverage -lgcov -o s21_string
	./s21_string
	lcov -t "./s21_string" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

clean:
	rm -rf s21_string *.a $(OBJECTS) a.out *.gcno *.gcda report app.info