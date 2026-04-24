CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/graph.c
DEMO = demo/shortest_dfs_demo.c
OBJ = graph.o

all: demo_run

lib:
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

demo_run: lib
	$(CC) $(CFLAGS) $(DEMO) $(OBJ) -o shortest_dfs


clean:
	rm -f *.o shortest_dfs