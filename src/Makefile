CC=g++ -std=c++17 
GCC =$(CC) -Wall -Wextra -Werror -g
CHECKFLAGS=-lgtest
REPORTDIR=gcov_report
GCOV=--coverage -pthread
OS = $(shell uname)

all: test clean

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css matrix_test report *.txt *.dSYM ./$(REPORTDIR)

s21_matrix.a:
	$(GCC) -c s21_*.cpp -o matrix.o
	ar rcs matrix.a matrix.o

test: clean
	$(GCC) $(GCOV) -c s21_*.cpp 
	$(GCC) -c test.cpp $(CHECKFLAGS)
	$(GCC) $(GCOV) -o matrix_test test.o s21_*.o $(CHECKFLAGS)
	./matrix_test

mytest: 
	@echo --------------------MYTEST-----------------------
	$(GCC) -std=c++17 -o  matrix s21_*.cpp main.cpp -lm -g
	@./matrix
	@rm matrix

cppcheck:
	@echo -------------------CPPCHECK------------------------
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp

clang:
	@echo -------------------CLANG_FORMAT------------------------
	@ cp ../../materials/linters/.clang-format .
	#clang-format -n -style=Google *.cpp *.h
	clang-format -i -style=Google *.cpp *.h
	@rm clang-format


leaks: test
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./matrix_test
else
	leaks -atExit --leak-check=full --show-leak-kinds=all  ./matrix_test 
endif

gcov_report: test
	lcov --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html
