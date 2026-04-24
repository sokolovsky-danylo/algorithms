CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -std=c11
LDFLAGS = -lm

SRC = src/hash_code.c src/linear_probing_impl.c
DEMO = demo/parking_simulation.c
OBJ = $(SRC:.c=.o)

all: parking_simulation

parking_simulation: $(OBJ) $(DEMO)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o parking_simulation