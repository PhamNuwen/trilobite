#include <stdarg.h>
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "list.h"

list_t list_push(list_t list, void *x){
	list_t p;
	NEW(p);
	//((p) = ALLOC((long)sizeof *(p)));
	p->elem = x;
	p->next = list;
	return p;
}

list_t list_new_list(void *x, ...){
	va_list ap;
	list_t list, *p = &list;

	va_start(ap, x);
	for(;x;x = va_arg(ap, void* )){
		NEW(*p);
		(*p)->elem = x;
		p = &(*p)->next;
	}
	*p = NULL;
	va_end(ap);
	return list;
}

list_t list_append(list_t list, list_t tail){
	list_t *p=&list;
	while(*p){
		p=&(*p)->next;
	}
	*p=tail;
	return list;
}

list_t list_copy(list_t list){
	list_t head, *p=&head;
	for(;list;list =list->next ){
		NEW(*p);
		(*p)->elem=list->elem;
		p=&(*p)->next;
	}
	*p=NULL;
	return head;
}

list_t list_pop(list_t list, void **x){
	if(list){
		list_t head = list->next;
		if(x){
			*x = list->elem;
		}
		FREE(list);
		return head;
	}else
		return list;
}

list_t list_reverse(list_t list){
	list_t head = NULL, next;
	for(;list;list=next){
		next = list->next;
		list->next = head;
		head = list;
	}
	return head;
}

int list_length(list_t list){
	int n;
	for(n=0;list;list=list->next){
		n++;
	}
	return n;
}

void list_free(list_t* list){
	list_t next;
	assert(list);
	for(;*list;*list=next){
		next=(*list)->next;
		FREE(*list);
	}
}

void list_map(list_t list, void apply(void **x, void *cl), void *cl){
	assert(apply);
	for(;list;list = list->next)
		apply(&list->elem, cl);
}

void **list_to_array(list_t list, void *end){
	int i, n=list_length(list);
	void **array=ALLOC((n+1)*sizeof(*array));
	for(i=0;i<n;i++){
		array[i]=list->elem;
		list=list->next;
	}
	array[i]=end;
	return array;
}
