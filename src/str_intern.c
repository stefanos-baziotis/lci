#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef uint8_t byte_t;

void *srealloc(void *p, size_t new_size) {
	p = realloc(p, new_size);
	if(p == NULL) {
		perror("srealloc() failed\n");
		exit(1);
	}
	return p;
}

void *smalloc(size_t size) {
	void *p = malloc(size);
	if(p == NULL) {
		perror("smalloc() failed\n");
		exit(1);
	}
	return p;
}

void *scalloc(size_t num_elems, size_t elem_size) {
	void *p = calloc(num_elems, elem_size);
	if(p == NULL) {
		perror("scalloc() failed\n");
		exit(1);
	}
	return p;
}

// -------------- STRING INTERNING -----------------

// TODO(stefanos): Strings should be const chars. It's one of the few
// places that const might catch bugs.
typedef struct interned_str {
	size_t len;
	char *str;
} interned_str_t;



static size_t interns_len;
static size_t interns_cap;
static interned_str_t *interns;

static void push_str(size_t len, char *str) {
	size_t new_interns_len = interns_len + 1;
	if(new_interns_len > interns_cap || interns == NULL) {  // grow
		// overflow check
		assert(interns_cap <= ((SIZE_MAX - 1) / 2));
		// minimum of 16 items
		size_t new_interns_cap = MAX(2 * interns_cap + 1, MAX(new_interns_len, 16));
		assert(new_interns_cap <= SIZE_MAX / sizeof(interned_str_t));
		size_t new_size = new_interns_cap * sizeof(interned_str_t);
		interns_cap = new_interns_cap;
		interns = (interned_str_t *)srealloc(interns, new_size);
	}
	interns[interns_len].len = len;
	interns[interns_len].str = str;
	interns_len++;
}

// NOTE(stefanos): str_intern_range() is useful when we have input come
// from a big string buffer (like reading the whole file in a single buffer)
// where strings are marked by 'start' and 'end' pointers. Here, only the
// str_intern() is used publicly, but str_intern_range() is left for
// possible future use.

// NOTE(stefanos): That eventually should a hash-table because that has
// O(n) but it's easy and effective enough for template version.
static char *str_intern_range(char *start, char *end) {
	size_t len = end - start;
	for (size_t i = 0; i != interns_len; ++i) {
		// NOTE(stefanos): You may assume that because we test interns[i].len == len,
		// that we just need to strcmp, BUT consider that string starting at 'start' is
		// not necessarilly NULL-terminated at 'end' and so strcmp() might yield wrong result.
		if (interns[i].len == len && strncmp(interns[i].str, start, len) == 0) {
			return interns[i].str;
		}
	}
	char *str = (char *) smalloc(len + 1);
	memcpy(str, start, len);
	str[len] = '\0';
	push_str(len, str);
	return str;
}

// NOTE(stefanos): That could be done faster, but that's easier.
char *str_intern(char *str) {
	return str_intern_range(str, str + strlen(str));
}

void str_intern_initialize(void) {
	interns_len = 0;
	interns_cap = 0;
	interns = NULL;
}

void str_intern_free(void) {
	for (size_t i = 0; i != interns_len; ++i) {
		free(interns[i].str);
	}
	free(interns);
}
