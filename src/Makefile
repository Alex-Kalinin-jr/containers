CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++17 -g
GCOV= --coverage
#our path
ROAD=.
#our file with main function
TESTNAME=test2.cc
#our output binary file
FILENAME=stack
#our first file for compiling library. !!!ATTNTN!!! filename is libname
FILE1=test

CHECKFLAGS=-fprofile-arcs -ftest-coverage

OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=-lgtest -lrt -lm -lsubunit -lpthread
  OPEN=xdg-open
else
  LIBS=-lgtest
  OPEN=open
endif




all: test test_without_leaks leaks clean gcov_report clean

test: $(FILE1).a
	$(CC) $(FLAGS) $(TESTNAME) -L . $(FILE1).a $(LIBS) -o $(ROAD)/$(FILENAME)
	make run

test_without_leaks: $(FILE1).a
	$(CC) $(FLAGS) $(TESTNAME) -L . $(FILE1).a $(LIBS) -D without_leaks -o $(ROAD)/$(FILENAME)
	make run

gcov_report: $(FILE1).a
	g++ $(CHECKFLAGS) $(TESTNAME) -L . $(FILE1).cc $(LIBS) -o $(FILENAME)
	./$(FILENAME)
	lcov -t "s21_matrix" -o s21_matrix.info --include */src/*.cc -c -d .
	genhtml -o report s21_matrix.info
	gcov s21_matrix.info -f
	rm -rf *.gcda *.gcdo *.gcov *.gcno *.info *dSYM
	$(OPEN) report/index.html

$(FILE1).a: $(FILE1).o
	ar -rcs $(FILE1).a $(FILE1).o

$(FILE1).o: $(FILE1).cc
	$(CC) $(FLAGS) -c $(FILE1).cc  -o $(FILE1).o

run:
	$(ROAD)/$(FILENAME)

style:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i -n *.cc *.h

leaks: test_without_leaks
	leaks -atExit -- $(ROAD)/$(FILENAME)

clean:
	rm -rf $(ROAD)/$(FILENAME) *.o *.dSYM *.gcda *.gcdo *.gcov *.gcno *.info *dSYM *.o *.out *.a report
