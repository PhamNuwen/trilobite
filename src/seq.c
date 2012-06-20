#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "assert.h"
#include "array.h"
#include "arrayrep.h"
#include "seq.h"
#include "mem.h"

struct seq{
	struct array array;
	int length;
	int head;
};

static void expand(seq_t seq){
	int n=seq->array.length;
	array_resize(&seq->array, 2*n);
	if(seq->head>0){
		void **old=&((void **)seq->array.array)[seq->head];
		memcpy(old+n, old,(n-seq->head)*sizeof(void*));
		seq->head+=n;
	}
}

seq_t seq_new(int hint){
	seq_t seq;
	assert(hint>=0);
	NEWZ(seq);
	if(hint==0)
		hint=16;
	arrayrep_init(&seq->array, hint, sizeof(void *), ALLOC(hint*sizeof(void *)));
	return seq;
}

seq_t seq_new_seq(void *x, ...){
	va_list ap;
	seq_t seq=seq_new(0);
	va_start(ap, x);
	for(;x;x=va_arg(ap,void*))
		seq_push_back(seq,x);
	va_end(ap);
	return seq;
}

void seq_free(seq_t* seq){
	assert(seq && *seq);
	assert((void *)*seq == (void *)&(*seq)->array);
	array_free((array_t *)seq);
}

int seq_length(seq_t seq){
	assert(seq);
	return seq->length;
}

void *seq_get(seq_t seq, int i){
	assert(seq);
	assert(i>=0 && i<seq->length);
	return ((void **)seq->array.array)[(seq->head+i)%seq->array.length];
}

void *seq_put(seq_t seq, int i, void *elem){
	assert(seq);
	assert(i>=0 && i<seq->length);
	void *prev = ((void **)seq->array.array)[(seq->head+i)%seq->array.length];
	((void**)seq->array.array)[(seq->head+i)%seq->array.length]=elem;
	return prev;
}

void *seq_pop_back(seq_t seq){
	int i;
	assert(seq);
	assert(seq->length>0);
	i = --seq->length;
	return ((void **)seq->array.array)[(seq->head+i)%seq->array.length];
}

void *seq_pop_front(seq_t seq){
	void *x;
	assert(seq);
	assert(seq->length>0);
	x=((void **)seq->array.array)[(seq->head)%seq->array.length];
	seq->head = (seq->head+1)%seq->array.length;
	--seq->length;
	return x;
}

void *seq_push_back(seq_t seq, void *elem){
	assert(seq);
	if(seq->length == seq->array.length)
		expand(seq);
	int i = seq->length++;
	return ((void **)seq->array.array)[(seq->head+i)%seq->array.length]=elem;
}

void *seq_push_front(seq_t seq, void *elem){
	assert(seq);
	if(seq->length == seq->array.length)
		expand(seq);
	if(--seq->head<0)
		seq->head=seq->array.length-1;
	seq->length++;
	return ((void **)seq->array.array)[(seq->head)%seq->array.length]=elem;
}











