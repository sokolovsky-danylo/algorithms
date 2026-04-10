CC     = gcc
CFLAGS = -Wall -Wextra -O2 -g -Iinclude
TARGET = LLRB_tests

SRCS = src/LLRB_tests.c \
       src/BST.c        \
       src/LLRB.c       \
       src/LLRB_ops.c   \
       src/node.c

OBJS = $(SRCS:.c=.o)

# ── Build ────────────────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ── Utility ──────────────────────────────────────────────
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean