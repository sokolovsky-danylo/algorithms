
CC = gcc


CFLAGS = -std=c11 -Wall -Wextra -g
LDFLAGS = -lm


TARGET = percolation_simulation

OBJS = main.o PercolationStats.o percolation.o dynamic_connectivity.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

main.o: main.c PercolationStats.h
	$(CC) $(CFLAGS) -c main.c


PercolationStats.o: PercolationStats.c PercolationStats.h percolation.h
	$(CC) $(CFLAGS) -c PercolationStats.c

percolation.o: percolation.c percolation.h dynamic_connectivity.h
	$(CC) $(CFLAGS) -c percolation.c

dynamic_connectivity.o: dynamic_connectivity.c dynamic_connectivity.h
	$(CC) $(CFLAGS) -c dynamic_connectivity.c

clean:
	rm -f *.o $(TARGET)