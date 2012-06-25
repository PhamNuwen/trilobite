#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "assert.h"
#include "mem.h"
#include "thread.h"
#include "sem.h"

#define isempty(q) ((q)==NULL)

void _MONITOR(void) {}
extern void _ENDMONITOR(void);

static thread_t read = NULL;
static thread_t current;
static int nthreads;
static struct thread_t root;

struct thread{
    unsigned long *sp;
    thread_t link;
    thread_t *inqueue;
    thread_t handle;
    exception_frame_t *estack;
};

static void put(thread_t t, thread_t *q){
    assert(t);
    assert(t->inqueue == NULL && t->link == NULL);
    if(*q){
        t->link = (*q)->link;
        (*q)->link = t;
    }else
        t->link = t;
    *q = t;
    t->inqueue = q;
}

static thread_t get(thread_t *q){
    thread_t t;
    assert(!isempty(*q));
    t = (*q)->link;
    if(t==*q)
        *q=NULL;
    else
        (*q)->link = t->link;
    assert(t->inqueue == q);
    t->link = NULL;
    t->inqueue = NULL;
    return t;
}

static void delete(thread_t t, thread_t *q){
    thread_t p;
    assert(t->link && t->inqueue == q);
    assert(!isempty(*q));
    for(p=*q;p->link!=t;p=p->link)
        ;
    if(p==t)
        *q=NULL;
    else{
        p->link = t->link;
        if(*q==t)
            *q=p;
    }
    t->link = NULL;
    t->inqueue = NULL;
}

int thread_init(int preempt, ...){
    assert(preempt == 0 || preempt == 1);
    assert(current == NULL);
    root.handle = &root;
    current = &root;
    nthreads = 1;
    if(preempt){
        
    }
    return 1;
}

thread_t thread_self(void){
    assert(current);
    return current;
}

extern void _swith(thread_t from, thread_t to);

static void run(void){
    thread_t t = current;
    current = get(&ready);
    t->estack = _Ex_stack_top;
    _Ex_stack_top = current->estack;
    _switch(t, current);
    
}