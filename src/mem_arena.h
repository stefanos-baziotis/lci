/*  Interface for the memory arena

	Copyright (C) 2019 Stefanos Baziotis 
	This file is part of LCI
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details. */

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
