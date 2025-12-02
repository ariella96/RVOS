#ifndef MEM_H
#define MEM_H

// Initialize the heap
void init_heap();

// Allocate a block of memory of a given `alloc_size`.
// Returns the address of the allocated memory.
void* mem_alloc(unsigned short alloc_size);

// Free a block of memory at `address`.
void mem_free(void* address);

#endif