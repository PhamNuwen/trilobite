#ifndef THREAD_H
#define	THREAD_H
#include "exception.h"
typedef struct thread *thread_t;
extern const exception_t Thread_Failed;
extern const exception_t Thread_Alerted;
extern int thread_init(int preempt, ...);
extern thread_t thread_new(int apply(void *), void *args, int nbytes, ...);
extern void thread_exit(int code);
extern void thread_alert(thread_t t);
extern thread_t thread_self(void);
extern int thread_join(thread_t t);
extern void thread_pause(void);
#endif

