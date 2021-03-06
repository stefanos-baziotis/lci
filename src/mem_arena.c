/*  Simple memory arena

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
