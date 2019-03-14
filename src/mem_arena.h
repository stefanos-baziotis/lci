#ifndef MEM_ARENA_H
#define MEM_ARENA_H

#include <stdint.h>

#define KB(v) (v*1024LL)
#define MB(v) (v*KB(1024))
#define GB(v) (v*MB(1024))

void mem_arena_initialize(size_t);
void mem_arena_free(void);
size_t mem_arena_size(void);
void mem_arena_set_size(size_t);
void *mem_arena_push_bytes(size_t);

#define mem_arena_push_type(type) (type *) mem_arena_push_bytes(sizeof(type))
#define mem_arena_push_array(count, type) (type *) mem_arena_push_bytes(((size_t)(count))*sizeof(type))

#endif
