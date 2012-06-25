#ifndef SEM_H
#define	SEM_H

typedef struct sem{
    int count;
    void *queue;
}sem_t;

extern void sem_init(sem_t *s, int count);
extern sem_t *sem_new(int count);
extern void sem_wait(sem_t *s);
extern void sem_signal(sem_t *s);

#define LOCK(mutex) do {set_t *_yymutex = &(mutex);\
        sem_wait(_yymutex);
#define UNLOCK(mutex) sem_signal(_yymutex);}while(0)

#endif
