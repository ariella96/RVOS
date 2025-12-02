#include "mem.h"

extern void* STACK_TOP;

struct mem_block {
	unsigned char is_free;
	struct mem_block* next;
};

struct mem_block* const heap = (struct mem_block*) &STACK_TOP;

void init_heap() {
	heap->is_free = 1;
	heap->next = 0;

	return;
}

void* mem_alloc(unsigned short alloc_size) {
	void* addr = 0;

	struct mem_block* curr = heap;
	while (curr) {
		if (curr->is_free) {
			if (curr->next) {
				unsigned short free_size = ((char*) curr->next) - ((char*) (curr + 1));
				if (free_size >= alloc_size) {
					curr->is_free = 0;
					addr = curr + 1;

					if (free_size > alloc_size + sizeof(struct mem_block)) {
						struct mem_block* curr_next = curr->next;
						curr->next = ((struct mem_block*) ((char*) addr) + alloc_size);
						curr->next->is_free = 1;
						curr->next->next = curr_next;
					}

					break;
				} else {
					curr = curr->next;
					continue;
				}
			} else {
				addr = curr + 1;
				curr->is_free = 0;
				curr->next = (struct mem_block*) (((char*) addr) + alloc_size);
				curr->next->is_free = 1;
				curr->next->next = 0;
				break;
			}
			break;
		} else {
			curr = curr->next;
		}
	}

	return addr;
}

void coalesce() {
	struct mem_block* curr = heap;
	while (curr) {
		if (curr->is_free && curr->next && curr->next->is_free) {
			curr->next = curr->next->next;
		} else {
			curr = curr->next;
		}
	}

	return;
}

void mem_free(void* address) {
	struct mem_block* block = ((struct mem_block*) address) - 1;
	block->is_free = 1;

	coalesce();

	return;
}