#include <limits.h>
#include <stddef.h>
#include "mem.h"
#include "assert.h"
#include "arith.h"
#include "set.h"

static int cmpatom(const void *x, const void *y) {
	return x != y;
}
static unsigned hashatom(const void *x) {
	return (unsigned long)x>>2;
}

static int primes[] = { 509, 509, 1021, 2053, 4093, 8191, 16381, 32771, 65521, INT_MAX };

static set_t copy(set_t set, int hint){
	set_t nset;
	assert(set);
	nset=set_new(hint, set->cmp, set->hash);
	int i;
	struct member * q;
	for(i=0;i<set->size;i++){
		for(q=set->buckets[i];q;q=q->next){
			struct member *p;
			const void *member = q->member;
			int i=(*nset->hash)(member)%nset->size;
			NEW(p);
			p->member=member;
			p->next=nset->buckets[i];
			nset->buckets[i]=p;
			nset->length++;
		}
	}
	return nset;
}

set_t set_new(int hint, int cmp(const void *x, const void *y), unsigned hash(const void *x)){
	set_t set;
	int i;
	assert(hint>=0);
	for(i=1; primes[i]<hint;i++);
	set=ALLOC(sizeof(*set)+primes[i-1]*sizeof(set->buckets[0]));
	set->size = primes[i-1];
	set->cmp = cmp ? cmp : cmpatom;
	set->hash = hash ? hash : hashatom;
	set->buckets = (struct member **)(set + 1);
	for(i=0;i<set->size;i++)
		set->buckets[i]=NULL;
	set->length=0;
	set->timestamp=0;
	return set;
}

int set_member(set_t set, const void *member){
	int i;
	struct member *p;
	assert(set);
	assert(member);
	i=(*set->hash)(member)%set->size;
	for(p=set->buckets[i];p;p=p->next)
		if((*set->cmp)(member, p->member)==0)
			break;
	return p!=NULL;
}

void set_put(set_t set, const void *member){
	int i;
	struct member *p;
	assert(set);
	assert(member);
	i=(*set->hash)(member)%set->size;
	for(p=set->buckets[i];p;p=p->next)
		if((*set->cmp)(member, p->member)==0)
			break;
	if(p==NULL){
		NEW(p);
		p->member=member;
		p->next=set->buckets[i];
		set->buckets[i]=p;
		set->length++;
	}else
		p->member=member;
	set->timestamp++;
}

void *set_remove(set_t set, const void* member){
	int i;
	struct member **pp;
	assert(set);
	assert(member);
	set->timestamp++;
	i=(*set->hash)(member)%set->size;
	for(pp=&set->buckets[i];*pp;pp=&(*pp)->next)
		if((*set->cmp)(member, (*pp)->member)==0){
			struct member *p=*pp;
			*pp=p->next;
			member=p->member;
			FREE(p);
			set->length--;
			return (void *)member;
		}
	return NULL;
}

int set_length(set_t set){
	assert(set);
	return set->length;
}


void set_free(set_t *set){
	assert(set && *set);
	if((*set)->length >0){
		int i;
		struct member *p, *q;
		for(i=0;i<(*set)->size;i++)
			for(p=(*set)->buckets[i];p;p=q){
				q=p->next;
				FREE(p);
			}
	}
	FREE(*set);
}

void set_map(set_t set,
		void apply(const void *member, void *cl),
		void *cl){
	int i;
	unsigned stamp;
	struct member *p;
	assert(set);
	assert(apply);
	stamp=set->timestamp;
	for(i=0;i<set->size;i++)
		for(p=set->buckets[i];p;p=p->next){
			apply(p->member, cl);
			assert(set->timestamp==stamp);
		}
}

void **set_to_array(set_t set, void *end){
	int i, j=0;
	void **array;
	struct member *p;
	assert(set);
	array=ALLOC((set->length+1)*sizeof(*array));
	for(i=0;i<set->size;i++)
		for(p=set->buckets[i];p;p=p->next)
			array[j++]=(void *)p->member;
	array[j]=end;
	return array;
}

set_t set_union(set_t s, set_t t){
	if(s==NULL){
		assert(t);
		return copy(t, t->size);
	}else if(t==NULL){
		assert(s);
		return copy(s, s->size);
	}else{
		set_t set = copy(s, arith_max(s->size, t->size));
		assert(s->cmp==t->cmp && s->hash==t->hash);
		int i;
		struct member *q;
		for(i=0;i<t->size;i++)
			for(q=t->buckets[i];q;q=q->next)
				set_put(set, q->member);
		return set;
	}
}

set_t set_inter(set_t s, set_t t){
	if(s==NULL){
		assert(t);
		return set_new(t->size, t->cmp, t->hash);
	}else if(t==NULL){
		assert(s);
		return set_new(s->size, s->cmp, s->hash);
	}else if(s->length < t->length)
		return set_inter(t, s);
	else{
		assert(s->cmp==t->cmp && s->hash==t->hash);
		set_t set = set_new(arith_min(s->size, t->size), s->cmp, s->hash);
		int i;
		struct member *q;
		for(i=0;i<t->size;i++)
			for(q=t->buckets[i];q;q=q->next)
				if(set_member(s,q->member)){
					struct member *p;
					const void *member = q->member;
					int i=(*set->hash)(member)%set->size;
					NEW(p);
					p->member=member;
					p->next=set->buckets[i];
					set->buckets[i]=p;
					set->length++;
				}
		return set;
	}
}

set_t set_minus(set_t t, set_t s){
	if(t==NULL){
		assert(s);
		return set_new(s->size,s->cmp, s->hash);
	}else if(s==NULL){
		return copy(t,t->size);
	}else{
		assert(s->cmp==t->cmp && s->hash==t->hash);
		set_t set = set_new(arith_min(s->size, t->size), s->cmp, s->hash);
		int i;
		struct member *q;
		for(i=0;i<t->size;i++)
			for(q=t->buckets[i];q;q=q->next)
				if(!set_member(s,q->next)){
					struct member *p;
					const void *member=q->member;
					int i=(*set->hash)(member)%set->size;
					NEW(p);
					p->member=member;
					p->next=set->buckets[i];
					set->buckets[i]=p;
					set->length++;
				}
		return set;
	}
}

set_t set_diff(set_t s, set_t t){
	if(s==NULL){
		assert(t);
		return copy(t, t->size);
	}else if(t==NULL){
		return copy(s, s->size);
	}else{
		assert(s->cmp==t->cmp && s->hash==t->hash);
		set_t set = set_new(arith_min(s->size, t->size), s->cmp, s->hash);
		int i;
		struct member *q;
		for(i=0;i<t->size;i++)
			for(q=t->buckets[i];q;q=q->next)
				if(!set_member(s, q->member)){
					struct member *p;
					const void *member = q->member;
					int i=(*set->hash)(member)%set->size;
					NEW(p);
					p->member=member;
					p->next=set->buckets[i];
					set->buckets[i]=p;
					set->length++;
				}
		for(i=0;i<s->size;i++)
			for(q=s->buckets[i];q;q=q->next)
				if(!set_member(s, q->member)){
					struct member *p;
					const void *member = q->member;
					int i=(*set->hash)(member)%set->size;
					NEW(p);
					p->member=member;
					p->next=set->buckets[i];
					set->buckets[i]=p;
					set->length++;
				}
		return set;
	}
}
