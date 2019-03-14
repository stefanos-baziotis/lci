#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem_arena.h"

static uint8_t *base;
static size_t size;
static size_t used;

void mem_arena_initialize(size_t sz) {
	size = sz;
	base = (uint8_t *) calloc(sz, 1);
	assert(base != NULL);
	used = 0;
}

void *mem_arena_push_bytes(size_t sz) {
	if(base == NULL) return NULL;
	// Don't realloc
	if(used + sz > size) return NULL;
	void *ret = base + used;
	used += sz;
	return ret;
}

void mem_arena_free(void) {
	if(base) free(base);
	base = NULL;
}

size_t mem_arena_size(void) {
	return used;
}

void mem_arena_set_size(size_t n) {
	used = n;
}
