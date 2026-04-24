CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
TEST_FLAGS = -lgtest -lgtest_main -pthread

all: demo test

demo: src/sort.o demo/shell_sort_demo.o
	$(CC) $^ -o shell_sort_example

src/sort.o: src/sort.c
	$(CC) $(CFLAGS) -c $< -o $@

test: tests/test_sort.cpp src/sort.o
	g++ -Iinclude $^ $(TEST_FLAGS) -o run_tests

clean:
	rm -f src/*.o demo/*.o shell_sort_example run_tests