#include <stdlib.h>
#include <stdio.h>
#include "exception.h"
#include "assert.h"

exception_frame_t *_Ex_stack_top = NULL;

void exception_raise(const exception_t *e, const char *file, int line){
	exception_frame_t *p = _Ex_stack_top;
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
