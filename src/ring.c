#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "assert.h"
#include "ring.h"
#include "mem.h"

struct ring{
	struct node{
		struct node *left, *right;
		void *elem;
	}*head;
	int length;
};

ring_t ring_new(void){
	ring_t ring;
	NEWZ(ring);
	ring->head = NULL;
	return ring;
}

ring_t ring_new_ring(void *x, ...){
	va_list ap;
	ring_t ring = ring_new();
	va_start(ap, x);
	for(;x;x=va_arg(ap,void*))
		ring_push_back(ring, x);
	va_end(ap);
	return ring;
}

void ring_free(ring_t *ring){
	struct node *p, *q;
	assert(ring && *ring);
	if((p=(*ring)->head)!=NULL){
		int n = (*ring)->length;
		for(;n-->0;p=q){
			q=p->right;
			FREE(p);
		}
	}
	FREE(*ring);
}

void ring_length(ring_t ring){
	assert(ring);
	return ring->length;
}
#if 0
void *ring_get(ring_t ring, int i){
	struct node *q;
	assert(ring);
	assert(i>=0 && i<ring->length);
	int n;
	q = ring->head;
	if(i<=ring->length/2)
		for(n=i;n-->0;)
			q = q->right;
	else
		for(n=ring->length-i;n-->0;)
			q = q->left;
	return q->elem;
}

void *ring_put(ring_t ring, int i, void *x){
	struct node *q;
	void *prev;
	assert(ring);
	assert(i>=0&&i<ring->length);
	int n;
	q = ring->head;
	if(i <= ring->length/2)
		for(n=i;n-->0;)
			q = q->right;
	else
		for(n = ring->length - i; n-- > 0;)
			q = q->left;
	prev = q->elem;
	q->elem = x;
	return prev;
}
#endif
void *ring_push_back(ring_t ring, void *x){
	struct node *p, *q;
	assert(ring);
	NEW(p);
	if((q = ring->head) != NULL){
		p->left = q->left;
		q->left->right = p;
		p->right = q;
		p->left = p;
	}else
		ring->head = p->left = p->right = p;
	ring->length++;
	return p->elem = x;
}

void *ring_push_front(ring_t ring, void *x){
	assert(ring);
	ring_push_back(ring, x);
	ring->head = ring->head->left;
	return x;
}















