#include <stdlib.h>
#include <stddef.h>
#include "assert.h"
#include "exception.h"
#include "mem.h"

const exception_t Mem_Fail={"Memory Allocation Failed"};

void *mem_alloc(long size, const char *file, int line){
	void *ptr;
	assert(size>0);
	ptr=malloc(size);
	if(ptr==NULL){
		if(file==NULL)
			RAISE(Mem_Fail);
		else
			exception_raise(&Mem_Fail, file, line);
	}
	return ptr;
}

void *mem_calloc(long elem_count, long elem_size, const char *file, int line){
	void *ptr;
	assert(elem_size>0 && elem_count>0);
	ptr = calloc(elem_count, elem_size);
	if(ptr==NULL){
		if(file==NULL)
			RAISE(Mem_Fail);
		else
			exception_raise(&Mem_Fail, file, line);
	}
	return ptr;
}

void mem_free(void *ptr, const char *file, int line){
	if(ptr)
		free(ptr);
}

void *mem_resize(void *ptr, long size, const char *file, int line){
	assert(ptr && size>0);
	ptr = realloc(ptr, size);
	if(ptr==NULL){
			if(file==NULL)
				RAISE(Mem_Fail);
			else
				exception_raise(&Mem_Fail, file, line);
	}
	return ptr;
}
