#ifndef ARENA_H
#define ARENA_H
#include "exception.h"
typedef struct arena *arena_t;
struct arena{
	arena_t prev;
	char *avail;
	char *limit;
};
extern const exception_t Arena_NewFailed;
extern const exception_t Arena_Failed;
extern void *arena_alloc(arena_t arena, long size, const char* file, int line);
extern void *arena_calloc(arena_t arena, long elem_count, long elem_size, const char* file, int line);
extern void arena_free(arena_t arena);
#endif
