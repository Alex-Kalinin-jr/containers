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
TESTNAME=./tests/test_main.cc
FILENAME=containers


FILE1=./tests/test_queue
FILE2=./tests/test_stack
FILE3=./tests/test_list
FILE4=./tests/test_multiset
FILE5=./tests/test_set
FILE6=./tests/test_vector
FILE7=./tests/test_map
FILE8=./tests/test_array
ALLFILES=$(FILE5).o $(FILE4).o $(FILE3).o $(FILE2).o $(FILE1).o $(FILE6).o $(FILE7).o
# ALLFILES=$(FILE3).o $(FILE1).o $(FILE2).o


all: test test_without_leaks leaks clean gcov_report clean

test: $(ALLFILES)
	$(CXX) $(CXXFLAGS) $(TESTNAME) -L . $(LIBS) $(ALLFILES) -o $(ROAD)/$(FILENAME)
	make run

noleaks: $(ALLFILES)
	$(CXX) $(CXXFLAGS) $(TESTNAME) -L . -D without_leaks $(LIBS) $(ALLFILES) -o $(ROAD)/$(FILENAME)

gcov_report: $(ALLFILES)
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

$(FILE4).o: $(FILE4).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FILE5).o: $(FILE5).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FILE6).o: $(FILE6).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FILE7).o: $(FILE7).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(FILE8).o: $(FILE8).cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	$(ROAD)/$(FILENAME)

style:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i -n *.cc *.h

leaks: noleaks
	leaks -atExit -- $(ROAD)/$(FILENAME)

clean:
	rm -rf $(ROAD)/$(FILENAME) *.o *.dSYM *.gcda *.gcdo *.gcov *.gcno *.info *dSYM *.o *.out *.a report ./tests/*.o