#ifndef MEMCPY_H
#define MEMCPY_H

#include <stddef.h>

// Copy `count` bytes from `src` to `dest`
void* memcpy(void* dest, const void* src, size_t count);

#endif