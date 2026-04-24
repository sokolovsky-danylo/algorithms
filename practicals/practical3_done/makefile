CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
TARGET = two_stacks

all: $(TARGET)

$(TARGET): src/stack.o demo/two_stacks.o
	$(CC) src/stack.o demo/two_stacks.o -o $(TARGET)

src/stack.o: src/stack.c include/stack.h
	$(CC) $(CFLAGS) -c src/stack.c -o src/stack.o

demo/two_stacks.o: demo/two_stacks.c include/stack.h
	$(CC) $(CFLAGS) -c demo/two_stacks.c -o demo/two_stacks.o

clean:
	rm -f src/*.o demo/*.o $(TARGET)