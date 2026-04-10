#ifndef ITEM_H
#define ITEM_H
#include <string.h>
#include <stdbool.h>

typedef char* Key;
typedef char* Value;

static inline bool less(Key a, Key b) { return strcmp(a, b) < 0; }
static inline bool greater(Key a, Key b) { return strcmp(a, b) > 0; }
static inline bool equal(Key a, Key b) { return strcmp(a, b) == 0; }
#endif