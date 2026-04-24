CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
TARGET = practical_8

# Визначаємо об'єктні файли
OBJ = BST.o node.o practical_8.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Шукаємо .c файли в папках src та tests
%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Спеціальне правило для BST.o, якщо файл називається BST.c (з великої)
BST.o: src/BST.c
	$(CC) $(CFLAGS) -c src/BST.c -o BST.o

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(TARGET) *.o