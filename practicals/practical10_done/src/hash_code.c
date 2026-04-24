#include "hash_code.h"
#include <stddef.h>

hash_t hashCodeInt(hash_t value) {
    return value;
}

hash_t hashCodeString(const char *str) {
    if (str == NULL) return 0;
    hash_t hash = 0;
    while (*str) {
        hash = 31 * hash + (unsigned char)(*str);
        str++;
    }
    return hash;
}