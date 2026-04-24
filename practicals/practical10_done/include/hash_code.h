#ifndef HASH_CODE_H
#define HASH_CODE_H

#include <stdint.h>

typedef int32_t hash_t;

hash_t hashCodeInt(hash_t value);
hash_t hashCodeString(const char *str);

#endif