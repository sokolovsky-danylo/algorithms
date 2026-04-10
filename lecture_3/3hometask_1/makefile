CC       = gcc
CXX      = g++
CFLAGS   = -std=c11   -Wall -Wextra -Wpedantic -g
CXXFLAGS = -std=c++17 -Wall -Wextra -g
INCLUDE  = -Iinclude

DEQUE_SRC = src/deque.c
TEST_SRC  = tests/dequetests.cpp
TEST_BIN  = deque_tests

.PHONY: all test clean

all: test

# GTest provides its own main() via -lgtest_main
# The C object and the C++ test file are linked together in one step
# Step 1: compile the C source with gcc
#         (void* implicit casts are valid C but rejected by g++ -fpermissive)
deque.o: $(DEQUE_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

# Step 2: compile C++ tests and link against the C object
$(TEST_BIN): deque.o $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^ -lgtest_main -lgtest -pthread

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN) deque.o