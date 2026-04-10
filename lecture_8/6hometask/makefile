CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

all: main

main: user/main.c src/BST.c src/node.c
	$(CC) $(CFLAGS) user/main.c src/BST.c src/node.c -o main

clean:
	rm -f main