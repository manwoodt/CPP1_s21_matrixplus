# CXX https://www.gnu.org/software/make/manual/html_node/Implicit-Variables.html
G =g++ -std=c++17
GCC =$(G) -Wall -Wextra -Werror -fsanitize=address  
LIBS =-lgtest -lpthread

all: test clean

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM

test: clean s21_matrix_oop.a
	$(GCC) s21_matrix_oop.a tests.cpp -o test $(LIBS) 
	./test --gtest_repeat=10 --gtest_break_on_failure --gtest_filter=* --gtest_color=yes --gtest_shuffle
	@make leak
	@make clang

s21_matrix_oop.a:
	$(G) -c s21_*.cpp
	ar rc s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a
	# rm *.o

mytest: 
	@echo --------------------Mytest-----------------------
	$(GCC) -std=c++17 -o  matrix s21_*.cpp main.cpp -lm
	@./matrix
	@rm matrix

gcov_report: clean
	$(GCC) --coverage tests.cpp s21_*.cpp -o test $(LIBS)
	chmod +x *
	./test
	lcov --ignore-errors mismatch -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	open ./report/index.html

leak:
	@echo --------------------MEMORY_LEAKS-----------------------
	@$(GCC) tests.cpp s21_*.cpp -lgtest -o leaks -g
	CK_FORK=no leaks --atExit -- ./leaks
	@rm ./leaks

clang:
	@echo -------------------CLANG_FORMAT------------------------
	clang-format -n s21_*.cpp s21_*.h tests.cpp
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.cpp