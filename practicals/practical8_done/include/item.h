#ifndef ITEM_H
#define ITEM_H 

#include <string.h>
#include <stdint.h>

typedef void *Value;
typedef char *Key;

#define less(A, B) (strcmp((char *)A, (char *)B) < 0)
#define greater(A, B) (strcmp((char *)A, (char *)B) > 0)
#define equal(key_a, key_b) (strcmp((key_a), (key_b)) == 0)

#endif