CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC = src/graph.c src/maze.c src/queue.c demo/main.c
OBJ = $(SRC:.c=.o)
EXEC = maze_solver

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f src/*.o demo/*.o $(EXEC)