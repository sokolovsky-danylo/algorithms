CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/digraph.c src/dfs.c
DEMO = demo/demo.c

all: topo_run

topo_run:
	$(CC) $(CFLAGS) $(SRC) $(DEMO) -o topo_sort

clean:
	rm -f topo_sort