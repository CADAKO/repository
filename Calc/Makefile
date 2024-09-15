CC = gcc -Wall -Werror -Wextra -std=c11
PROJECT = SmartCalc_v1.0.a
TESTS = tests/*.c
OS := $(shell uname)


ifeq ($(OS),Linux)
	FLAGS = -lcheck -lm -lpthread -lrt -lsubunit -fprofile-arcs -ftest-coverage
	OPEN_CMD = xdg-open
	QTFLAGS = CONFIG+=qtquickcompiler
else
	FLAGS = -lcheck -lm -lpthread -fprofile-arcs -ftest-coverage
	OPEN_CMD = open
	QTFLAGS = -spec macx-clang CONFIG+=qtquickcompiler
endif

$(PROJECT): clang
	$(CC) $(FLAGS) -c *.c
	ar -crs $(PROJECT) *.o

clang:
	-clang-format --style=Google -n *.c *.h frontend/main*.cpp frontend/main*.h tests/*.c

test: clean $(PROJECT)
	$(CC) $(TESTS) $(PROJECT) $(FLAGS) -o test
	./test

gcov_report:
	lcov -t "./test" -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html
	rm -rf *.gcno *gcda *.gco

dvi:
	open ./README.md

dist:
	mkdir SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/src
	mkdir SmartCalc_v1.0/src/frontend
	mkdir SmartCalc_v1.0/src/tests
	cp ./frontend/* "SmartCalc_v1.0/src/frontend"
	cp ./tests/* "SmartCalc_v1.0/src/tests"
	cp *.c *.h SmartCalc_v1.0/src
	cp -R Makefile SmartCalc_v1.0/src
	cp -R README.md SmartCalc_v1.0/src
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	rm -rf SmartCalc_v1.0

install: uninstall
	mkdir build
	cd build && qmake ../frontend/Calc.pro $(QTFLAGS) && /usr/bin/make -j8
	cd build && rm -rf *.o *.cpp *.h Makefile
	open ./build/

uninstall:
	rm -rf build

clean:
	rm -rf test $(PROJECT) *.a *.o *.gcno *gcda *.gcov gcov report report.info

all: clean $(PROJECT) test gcov_report


memtest: clean $(PROJECT)
	$(CC) -g $(TESTS) $(PROJECT) $(FLAGS) -o mem
	valgrind -s --leak-check=full --leak-resolution=med --track-origins=yes ./mem

mem: clean $(PROJECT)
	$(CC) -g $(PROJECT) -o mem -lm
	valgrind -s --leak-check=full --leak-resolution=med --track-origins=yes ./mem

installapp:
	sudo apt-get install -y lcov check valgrind clang-format qt5-qmake
