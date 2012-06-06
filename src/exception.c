#include <stdlib.h>
#include <stdio.h>
#include "exception.h"
#include "assert.h"

exception_frame *_Ex_stack_top = NULL;

void exception_raise(const exception *e, const char *file, int line){
	exception_frame *p = _Ex_stack_top;
	assert(e);
	if (p==NULL){
		fprintf(stderr, "Uncaught exception");
		if (e->reason)
			fprintf(stderr, ": %s", e->reason);
		if (file && line > 0)
			fprintf(stderr, " raised at %s:%d\n", file, line);
		fflush(stderr);
		abort();
	}
	p->exception = e;
	p->file = file;
	p->line = line;
	_Ex_stack_top = _Ex_stack_top->prev;
	longjmp(p->env, exception_raised);
}
