#ifndef SEQ_H
#define SEQ_H
typedef struct seq* seq_t;
extern seq_t seq_new(int hint);
extern seq_t seq_new_seq(void *x, ...);
extern void seq_free(seq_t* seq);
extern int seq_length(seq_t seq);
extern void *seq_get(seq_t seq, int i);
extern void *seq_put(seq_t seq, int i, void *elem);
extern void *seq_push_front(seq_t seq, void *elem);
extern void *seq_push_back(seq_t seq, void *elem);
extern void *seq_pop_front(seq_t seq);
extern void *seq_pop_back(seq_t seq);

#endif
