#ifndef LIST_H
#define LIST_H

typedef struct list *list_t;
struct list{
	list_t next;
	void *elem;
};

extern list_t list_append(list_t list, list_t tail);
extern list_t list_copy(list_t);
extern list_t list_new_list(void *x,...); //NULL terminated param list
extern list_t list_pop(list_t list, void **x);
extern list_t list_push(list_t list, void *x);
extern list_t list_reverse(list_t list);
extern int list_length(list_t list);
extern void list_free(list_t* list);
extern void list_map(list_t list, void apply(void **x, void *cl), void *cl);
extern void **list_to_array(list_t list, void *end);

#endif
