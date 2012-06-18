#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "exception.h"
#include "arena.h"

const exception_t Arena_NewFailed = {"Arena Creation Failed"};
const exception_t Arena_Failed = {"Arena Allocation Failed"};

static arena_t freechunks;
static int nfree;

#define THRESHOLD 10

union align{
	int i;
	long l;
	long *lp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
};

union header{
	struct arena b;
	union align a;
};

arena_t arena_new(void){
	arena_t arena = malloc(sizeof(arena_t));
	if(arena==NULL)
		RAISE(Arena_NewFailed);
	arena->prev=NULL;
	arena->limit=arena->avail=NULL;
	return arena;
}

void arena_dispose(arena_t *ap){
	assert(ap && *ap);
	arena_free(*ap);
	free(ap);
	*ap=NULL;
}

void *arena_alloc(arena_t arena, long size, const char *file, int line){
	assert(arena);
	assert(size>0);
	size = ((size + sizeof(union align)-1)/(sizeof(union align)))*(sizeof(union align));
	while(size > arena->limit - arena->avail){
		arena_t ptr;
		char *limit;
		if((ptr = freechunks)!=NULL){
			freechunks=freechunks->prev;
			nfree--;
			limit = ptr->limit;
		}else{
			long m = sizeof(union header) + size + 10*1024;
			ptr = malloc(m);
			if(ptr == NULL){
				if(file==NULL)
					RAISE(Arena_Failed);
				else
					exception_raise(&Arena_Failed, file, line);
			}
			limit = (char *)ptr+m;
		}
		*ptr=*arena;
		arena->avail = (char *)((union header *)ptr +1);
		arena->limit = limit;
		arena->prev = ptr;

	}
	arena->avail += size;
	return arena->avail - size;
}

void *arena_calloc(arena_t arena, long elem_count, long elem_size, const char *file, int line){
	void *ptr;
	assert(elem_count>0);
	ptr = arena_alloc(arena, elem_count * elem_size, file, line);
	memset(ptr, 0, elem_count * elem_size);
	return ptr;
}

void arena_free(arena_t arena){
	assert(arena);
	while(arena->prev){
		struct arena tmp = *arena->prev;
		if(nfree < THRESHOLD){
			arena->prev->prev = freechunks;
			freechunks = arena->prev;
			nfree++;
			freechunks->limit = arena->limit;
		}
		else{
			free(arena->prev);
		}
		*arena = tmp;
	}
	assert(arena->limit == NULL);
	assert(arena->avail == NULL);
}
