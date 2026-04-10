CC       = gcc
CXX      = g++
CFLAGS   = -std=c11   -Wall -Wextra -Wpedantic -g
CXXFLAGS = -std=c++17 -Wall -Wextra -g
INCLUDE  = -Iinclude

RQ_SRC   = src/randomized.c
TEST_SRC = tests/randomizedtests.cpp
TEST_BIN = rq_tests

.PHONY: all test clean

all: test

rq.o: $(RQ_SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

$(TEST_BIN): rq.o $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ $^ -lgtest_main -lgtest -pthread

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN) rq.o