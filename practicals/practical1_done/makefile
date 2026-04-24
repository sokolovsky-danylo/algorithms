CXX = g++
CC = gcc
CXXFLAGS = -std=c++20 -Wall -g -I./include -I/usr/include/gtest
CFLAGS = -Wall -g -I./include

GTEST_LIBS = -lgtest -lgtest_main -pthread

SRC_C = src/union_find.c
SRC_CXX = test/lecture_1_tests.cpp

OBJ_C = $(SRC_C:.c=.o)
OBJ_CXX = $(SRC_CXX:.cpp=.o)

TARGET = lecture_1_test

all: $(TARGET)

$(TARGET): $(OBJ_C) $(OBJ_CXX)
	$(CXX) $(CXXFLAGS) $(OBJ_C) $(OBJ_CXX) -o $(TARGET) $(GTEST_LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test/%.o: test/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) src/*.o test/*.o