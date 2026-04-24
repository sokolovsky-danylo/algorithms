CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
TARGET = main
LIB_DIR = ./lib
LIBS_DYNAMIC = -L$(LIB_DIR) -lstatistical_measures_dynamic -lm
LIBS_STATIC = -L$(LIB_DIR) -lstatistical_measures_static -lm

all: $(TARGET)_dynamic $(TARGET)_static

$(TARGET)_dynamic: $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET)_dynamic $(TARGET).o $(LIBS_DYNAMIC) -Wl,-rpath=$(LIB_DIR)

$(TARGET)_static: $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET)_static $(TARGET).o $(LIBS_STATIC)

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

clean:
	rm -f $(TARGET)_dynamic $(TARGET)_static *.o