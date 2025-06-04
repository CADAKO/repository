CC=gcc
FLAGS=-Wall -Wextra -Werror -std=c11
all: s21_grep

clean:
	rm -rf s21_grep
	rm -rf .clang-format

s21_grep:
	$(CC) $(FLAGS) s21_grep.c -o s21_grep

test:
	./test_func_grep.sh
