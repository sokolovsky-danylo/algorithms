# Variables
CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Iinclude -g
LDFLAGS = -lm
GTEST_FLAGS = -lgtest -lgtest_main -lpthread

# Default target builds both main programs
all: brute fast

# 1. Compile the C library logic into an object file
# This is the "brain" of your project
point.o: src/point.c include/point.h
	$(CC) $(CFLAGS) -c src/point.c -o point.o

# 2. Build the Brute Force program - Complexity O(N^4)
brute: src/brute.c point.o
	$(CC) $(CFLAGS) src/brute.c point.o -o brute $(LDFLAGS)

# 3. Build the Fast Sorting program - Complexity O(N^2 log N)
fast: src/fast.c point.o
	$(CC) $(CFLAGS) src/fast.c point.o -o fast $(LDFLAGS)

# 4. Build the Google Test executable
# We use G++ here because GTest is a C++ library
test: tests/test_point.cpp point.o
	$(CXX) $(CFLAGS) tests/test_point.cpp point.o -o test_point $(GTEST_FLAGS)

# Shortcut to run tests
run_test: test
	./test_point

# Clean up files to start fresh
clean:
	rm -f *.o brute fast test_point