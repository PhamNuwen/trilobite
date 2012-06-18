#ifndef MEM_H
#define MEM_H
#include "exception.h"
extern const exception_t Mem_Failed;
extern void *mem_alloc(long size, const char *file, int line);
extern void *mem_calloc(long elem_count, long elem_size, const char *file, int line);
extern void mem_free(void *ptr, const char *file, int line);
extern void *mem_resize(void *ptr, long size, const char *file, int line);
#define ALLOC(size) mem_alloc((size), __FILE__, __LINE__)
#define CALLOC(count, size) mem_calloc((count), (size), __FILE__, __LINE__)
#define NEW(elem) ((elem) = ALLOC((long)sizeof *(elem)))
#define NEWZ(elem) ((elem) = CALLOC(1, sizeof *(elem)))
#define FREE(elem) ((void)mem_free((elem), __FILE__, __LINE__), (elem)=NULL)
#define RESIZE(ptr, size) ((ptr) = mem_resize((ptr), size, __FILE__, __LINE__))
#endif
