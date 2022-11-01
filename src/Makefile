CC = g++
LDFLAGS = -O2 -Wall -Wextra -std=c++17
SOURCE = $(wildcard tests/test_*.cc)
HEADER = $(wildcard s21_*.h)
OS := $(shell uname -s)
ifeq ($(OS), Darwin)
	OPEN_CMD = open
	ADD_LIBS = -lgtest
	LEAK_CHECK = leaks
	LEAK_ARGS = -atExit --
endif
ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
	ADD_LIBS = -lgtest -lpthread
	LEAK_CHECK = valgrind
	LEAK_ARGS = --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes
endif

all: clean check test

test: clean $(SOURCE)
	$(CC) $(LDFLAGS) -o $@ $(SOURCE) $(ADD_LIBS)
	-./$@

leaks_test: clean $(SOURCE)
	$(CC) $(LDFLAGS) -o $@ $(SOURCE) $(ADD_LIBS)
	-$(LEAK_CHECK) $(LEAK_ARGS) ./$@

gcov_report: clean $(SOURCE)
	-mkdir report
	$(CC) $(LDFLAGS) -o $@ $(SOURCE) $(ADD_LIBS) --coverage
	-./$@
	gcov -n $(SOURCE)
	lcov -t s21_containers -o s21_containers.info -c -d . --no-external
	genhtml -o report s21_containers.info
	rm -f $@ *.gcda *.gcno *.info
	$(OPEN_CMD) ./report/index.html

style:
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i -n *.cc *.h

check: $(SOURCE) $(HEADER)
	clang-format -style="{BasedOnStyle: Google, IndentWidth: 4}" -i -n $(SOURCE) $(HEADER)
	cppcheck --std=c++17 -x c++ --enable=all --suppress=missingIncludeSystem $(SOURCE) $(HEADER)

clean:
	rm -f ./test ./leaks_test *.o && rm -rf report/