all: test

test: clean
				g++ -std=c++17 --coverage s21_vector.h tests/s21_main_tests.cc -o test -lgtest -lpthread
				./test
clean:
				rm -f *.a *.o *.out
				rm -f *.gcno *.gcda *.info test CPPLINT.cfg