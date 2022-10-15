SHELL = /bin/sh
OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=-lgtest -lrt -lm -lsubunit -lpthread
  OPEN=xdg-open
else
  LIBS=-lgtest
  OPEN=open
endif


CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++17 -g
GCOV= --coverage -O0


ROAD=.
TESTNAME=test_main.cc
FILENAME=containers


FILE1=test_queue
FILE2=test_stack
FILE3=test_list
ALLFILES=$(FILE1).o $(FILE2).o $(FILE3).o


all: test test_without_leaks leaks clean gcov_report clean

test: $(FILE1).o $(FILE2).o $(FILE3).o
	$(CXX) $(CXXFLAGS) $(TESTNAME) -L . $(LIBS) $(ALLFILES) -o $(ROAD)/$(FILENAME)
	make run

noleaks: $(FILE1).o $(FILE2).o $(FILE3).o
	$(CXX) $(CXXFLAGS) $(TESTNAME) -L . -D without_leaks $(LIBS) $(ALLFILES) -o $(ROAD)/$(FILENAME)

gcov_report: $(FILE1).o $(FILE2).o $(FILE3).o
	$(CXX) $(GCOV) $(CXXFLAGS) $(TESTNAME) -L . $(LIBS) $(ALLFILES) -o $(ROAD)/$(FILENAME)
	$(ROAD)/$(FILENAME)
	lcov -t "$(FILENAME)" -o $(FILENAME).info --include */src/*.cc -c -d .
	genhtml -o report $(FILENAME).info
	gcov $(FILENAME).info -f
	rm -rf *.gcda *.gcdo *.gcov *.gcno *.info *dSYM
	$(OPEN) report/index.html


$(FILE1).o: $(FILE1).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FILE2).o: $(FILE2).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FILE3).o: $(FILE3).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	$(ROAD)/$(FILENAME)

style:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -n *.cc *.h

leaks: noleaks
	leaks -atExit -- $(ROAD)/$(FILENAME)

clean:
	rm -rf $(ROAD)/$(FILENAME) *.o *.dSYM *.gcda *.gcdo *.gcov *.gcno *.info *dSYM *.o *.out *.a report