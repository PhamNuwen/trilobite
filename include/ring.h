#ifndef RING_H
#define RING_H
typedef struct ring *ring_t;
extern ring_t ring_new(void);
extern ring_t ring_new_ring(void *x, ...);
extern void ring_free(ring_t *ring);
extern int ring_length(ring_t ring);
//extern void *ring_get(ring_t ring, int i);
//extern void *ring_put(ring_t ring, int i, void *x);
//extern void *ring_add(ring_t ring, int pos, void *x);
extern void *ring_push_front(ring_t ring, void *x);
extern void *ring_push_back(ring_t ring, void *x);
extern void *ring_remove(ring_t ring, void *x);
extern void *ring_pop_front(ring_t ring);
extern void *ring_pop_back(ring_t ring);
extern void ring_rotate(ring_t ring, int n);
#endif
