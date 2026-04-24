CC = gcc
CXX = g++
CFLAGS = -Iinclude -Wall -Wextra
CXXFLAGS = -Iinclude -Wall -Wextra
LDFLAGS = -lgtest -lgtest_main -lpthread

SRC = src/sorting.c
OBJ = $(SRC:.c=.o)
LIBRARY = libsorting.a

all: $(LIBRARY) demo tests_bin

$(LIBRARY): $(OBJ)
	ar rcs $@ $^

demo: demo/sort_demo.c $(LIBRARY)
	$(CC) $(CFLAGS) $< -L. -lsorting -o sort_demo

tests_bin: tests/test_sort.cpp $(LIBRARY)
	$(CXX) $(CXXFLAGS) $< -L. -lsorting $(LDFLAGS) -o run_tests

clean:
	rm -f src/*.o *.a sort_demo run_tests