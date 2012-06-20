#ifndef ARRAY_H
#define ARRAY_H
typedef struct array *array_t;
extern array_t array_new(int length, int size);
extern void array_free(array_t *array);
extern int array_length(array_t array);
extern int array_size(array_t array);
extern void *array_get(array_t array, int i);
extern void *array_put(array_t array, int i, void *elem);
extern void array_resize(array_t array, int length);
extern array_t array_copy(array_t array, int length);
#endif
