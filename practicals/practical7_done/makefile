CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -g
SRC = src/priority_queue.c src/heapsort.c
DEMO = demo/main.c
OBJ = $(SRC:.c=.o)

all: demo_run

demo_run: $(OBJ)
	$(CC) $(CFLAGS) $(DEMO) $(OBJ) -o demo_prog

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o demo_prog