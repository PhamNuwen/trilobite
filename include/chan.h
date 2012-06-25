#ifndef CHAN_H
#define	CHAN_H

typedef struct chan * chan_t;

extern chan_t chan_new(void);
extern int chan_send(chan_t c, const void *ptr, int size);
extern int chan_receive(chan_t c, void *ptr, int size);

#endif