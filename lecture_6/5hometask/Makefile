CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g
LDFLAGS = -lm

.PHONY: all clean test

all: convex_hull test_convex_hull

convex_hull: main.c convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -o $@ main.c convex_hull.c $(LDFLAGS)

test_convex_hull: test_convex_hull.c convex_hull.c convex_hull.h
	$(CC) $(CFLAGS) -o $@ test_convex_hull.c convex_hull.c $(LDFLAGS)

test: test_convex_hull
	./test_convex_hull

clean:
	rm -f convex_hull test_convex_hull
