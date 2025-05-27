#include "memcpy.h"

void* memcpy(void* dest, const void* src, size_t count) {
  for (int i = 0; i < count; i++) {
    ((unsigned char*) dest)[i] = ((unsigned char*)src)[i];
  }
  return dest;
}