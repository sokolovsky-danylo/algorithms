CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
CXXFLAGS = -Wall -Wextra -std=c++14 -Iinclude
LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
INC_DIR = include
DEMO_DIR = demo
TEST_DIR = tests
OBJ_DIR = obj
BIN_DIR = bin

# Вихідні файли
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: demo test

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Демо програма
demo: $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(DEMO_DIR)/main.c $(OBJ) -o $(BIN_DIR)/demo

# Модульні тести
test: $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/test_llrb.cpp $(OBJ) -o $(BIN_DIR)/test_llrb $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)