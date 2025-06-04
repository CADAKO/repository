CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
all: s21_cat

clean:
	rm -rf s21_cat
	rm -rf .clang-format

s21_cat:
	$(CC) $(FLAGS) s21_cat.c s21_cat.h -o s21_cat

test:
	./test_func_cat.sh