CC = g++
LDFLAGS = -Wall -Wextra -Werror -std=c++17
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
	ADD_LIBS = -lgtest -lrt -lm -lsubunit -lpthread
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

style: $(SOURCE) $(HEADER)
	clang-format -i $(SOURCE) $(HEADER)

clean:
	rm -f ./test ./leaks_test *.o && rm -rf report/
